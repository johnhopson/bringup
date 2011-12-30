/* -------------------  (c)1998 john hopson  -------------------

  Board Bring-Up Program

 - This is a simple program used to bring up a first-article microcontroller
   board and to test the compiler/debugger toolchain to which it is attached.

 - In its simplest form, this program is purely computational.  It requires
   no OS and not even any I/O, making it useful for establishing the 
   compiler/debugger/CPU path.  Once that path is established, bringup can 
   add printf and file I/O for further testing.

 - This program can also serve as a simple first-order performance benchmark.

 - See 'readme.md' for example builds.

 - Written and tested with gcc 4.2.1 on OS X.

 - Hosted at github.com/johnhopson/bringup

 - 'license' file has release terms
*/

#include  <stdint.h>
 
#define  VERSION  "1.1"


//  The highest number to check for prime.  
//
// - Data memory consumption is roughly 
//   proportional to this constant.

#ifndef  MAX_PRIME_CANDIDATE
#define  MAX_PRIME_CANDIDATE  1000
#endif


//  Number of times to call CalcPrime()
//  before exiting.  0 = infinite.

#ifndef  NUM_CYCLES
#define  NUM_CYCLES  1
#endif


//  Measure elapsed time

#ifdef  MEASURE_TIME
#include <time.h>
#endif


//  Define USE_PRINTF to generate console output.
//  Leave undefined to turn off consolde output.

#ifdef  USE_PRINTF
#include <stdio.h>
#define  PRINTF(a,b)  printf(a,b)
#else
#define  PRINTF(a,b)
#endif


//  Define LOG_FILE to a file name to have 
//  output go to said file.  Leaving it undefined
//  turns off file I/O.

#ifdef  LOG_FILE
#include <stdio.h>
#include <stdlib.h>
FILE  * LogFile;
#define  FPRINTF(a,b,c)  fprintf(a,b,c)
#else
#define  FPRINTF(a,b,c)
#endif


//  Output messages to console and/or file
#define  OUTPUT(fmt, var)  PRINTF(fmt, var);  \
                           FPRINTF( LogFile, fmt, var )


static uint8_t  IsPrime[ MAX_PRIME_CANDIDATE+1 ];  
const  uint8_t  Yes = 1;
const  uint8_t  No  = 0;


/* ---------------------------------------------------------------------
   Calculate primes and optionally print results to screen and/or file.
   
  - The algorithm is the classic prime sieve of Eratosthenes.  It 
    finds all the prime numbers between 2 and MAX_PRIME_CANDIDATE.  
    It uses a 'negative list' approach.  All factors of 2 are elim-
    inated from the list.  Then factors of 3, then 4, and so on up 
    to the square root of MAX_PRIME_CANDIDATE.  Only primes 
    survive that pruning.
 */

void  CalcPrimes()
{
    uint32_t  i, j;  
      

    OUTPUT( "\nThe primes from 2 to %d are:\n", MAX_PRIME_CANDIDATE );


    //  Initially, mark all as prime.
    for (i = 2;                                
         i <= MAX_PRIME_CANDIDATE;
         i++)
    {
       IsPrime[i] = Yes;    
    }


    //  Mark all factors of numbers from 2 to 
    //  sqrt(MAX_PRIME_CANDIDATE) as not prime.
    
    for (i = 2;
         i*i <= MAX_PRIME_CANDIDATE;
         i++)
    {
        if (IsPrime[i] == Yes)   
        {          
            for (j = i+i;   
                 j <= MAX_PRIME_CANDIDATE; 
                 j += i) 
            {
                IsPrime[j] = No;
            }                              
        }
    }


    //  Print out all primes.
    for (i = 2;                       
         i <= MAX_PRIME_CANDIDATE;
         i++)
    {
        if (IsPrime[i] == Yes)
        {
            OUTPUT( "%d\n", i );
        }
    }
}



/* ---------------------------------------------------------------------
   Main program entry point. 
 */

int  main( int argc,  char* argv[] )
{
    uint32_t  cycle;

    
#ifdef  MEASURE_TIME
    clock_t  StartTime = clock();    
#endif

        
#ifdef  LOG_FILE
    if (!(LogFile = fopen( LOG_FILE, "wb" )))
    {
        PRINTF( "Unable to open output file: %s", LOG_FILE );
        exit(1);
    }
#endif    


    OUTPUT( "bringup %s  (" __DATE__ ")\n", VERSION );
    
    for (cycle = 1;                       
         cycle <= NUM_CYCLES;
         cycle++)
    {
        OUTPUT( "\nCycle: %d" , cycle );
        CalcPrimes();
    }


#ifdef  MEASURE_TIME
    OUTPUT( "\nTest time: %ldms\n\n",  \
            (clock() - StartTime)/(CLOCKS_PER_SEC / 1000) );
#endif  


#ifdef  LOG_FILE
    fclose( LogFile );
#endif    

    return 0;
}
