/* -------------------  Public Domain - 1998 - John Hopson  -------------------

  Board Bring-Up Program

 - This is a first-test program used to check out new boards or development
   tools.  It calculates the sieve of Eratosthenes using various compile-time
   parameters.
 
 - In its simplest configuration (undefine USE_PRINTF and OUTPUT_FILE), this 
   file is purely computational, making it useful for exercising new 
   compiler/debugger/target paths without requiring any target I/O.

 - This program can also serve as a simple first-order performance benchmark.
   
 - Example builds -
     gcc  -o bringup.exe  bringup.c
       Find primes from 2 to 1000 and exit. Purely computational.  
       Uses no I/O.
     
     gcc  -D NUM_CYCLES=0  -D USE_PRINTF  -o bringup.exe  bringup.c
      Find primes from 2 to 1000.  Run forever until stopped.  
      Print output to the console (but not to file).  
     
     gcc  -D MAX_PRIME_CANDIDATE=750  -D NUM_CYCLES=100  -D MEASURE_TIME \
          -D USE_PRINTF  -D OUTPUT_FILE=\"bringup.log\"                  \
          -o bringup.exe  bringup.c
      Uses all options.  Find primes from 2 to 750, 100 times, and exit. 
      Print elapsed time before exit.  Print output to console and to 
      file 'bringup.log'. 
        
 -------------------------- */

#define  VERSION  "0.9"


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


//  Define OUTPUT_FILE to a file name to have 
//  output go to said file.  Leaving it undefined
//  turns off file I/O.

#ifdef  OUTPUT_FILE
#include <stdio.h>
#include <stdlib.h>
FILE  * OutFile;
#define  FPRINTF(a,b,c)  fprintf(a,b,c)
#else
#define  FPRINTF(a,b,c)
#endif


//  Output messages to console and/or file
#define  OUTPUT(fmt, var)  PRINTF(fmt, var);  \
                           FPRINTF( OutFile, fmt, var )



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
    static char  IsPrime[ MAX_PRIME_CANDIDATE+1 ];  
    const  char  Yes = 1;
    const  char  No  = 0;

    int  i, j;  
      

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
    unsigned long  cycle;

    
#ifdef  MEASURE_TIME
    clock_t  StartTime = clock();    
#endif

        
#ifdef  OUTPUT_FILE
    if (!(OutFile = fopen( OUTPUT_FILE, "wb" )))
    {
        PRINTF( "Unable to open output file: %s", OUTPUT_FILE );
        exit(1);
    }
#endif    


    OUTPUT( "bringup %s  (" __DATE__ ")\n", VERSION );
  
  
#if  NUM_CYCLES > 0
    for (cycle = 1;                       
         cycle <= NUM_CYCLES;
         cycle++)
    {
        OUTPUT( "\nCycle: %ld" , cycle );
        CalcPrimes();
    }
#else
    while(1)
    {
        CalcPrimes();
    }
#endif


#ifdef  MEASURE_TIME
    OUTPUT( "\nTest time: %ldms\n\n",  \
            (clock() - StartTime)/(CLOCKS_PER_SEC / 1000) );
#endif  


#ifdef  OUTPUT_FILE
    fclose( OutFile );
#endif    

    return 0;
}
