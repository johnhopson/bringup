#bringup

bringup.c is intended to be the first file compiled with a new embedded toolset
or the first file run on a new embedded target.  It doesn't require an OS and,
by default, it doesn't use any I/O.  However, I/O is supported with 
compile-time parameters.

### Details
bringup.c finds prime numbers from 2 to a specified maximum.  By default, it
runs one cycle and exits, and is purely computational.  Console or file 
logging can be added at compile-time.  The algorithm is the 
[prime sieve of Eratosthenes](http://en.wikipedia.org/wiki/Sieve_of_eratosthenes).

### Usage

    gcc  -g -o bringup.exe  bringup.c

        Find primes from 2 to 1000 and exit. Purely computational.  With debug
        information (-g).  No I/O.
    
    gcc  -g -D NUM_CYCLES=0  -D USE_PRINTF  -o bringup.exe  bringup.c

        Find primes from 2 to 1000.  Run forever until stopped (NUM_CYCLES=0).  
        Print output to the console (but not to file).  
    
    gcc  -g  -D MAX_PRIME_CANDIDATE=750  -D NUM_CYCLES=100  
         -D MEASURE_TIME  -D USE_PRINTF  -D LOG_FILE=\"bringup.log\"
         -o bringup.exe  bringup.c

        Uses all options.  Find primes from 2 to 750, 100 times, and exit.  
        Print elapsed time.  Print output to console and to file 
        'bringup.log'.

### Other
bringup.c can be used as a simple first-order benchmark.  It's advantage is
simple and consistent configuration on any platform.  Comparisons are truly
apples-and-apples.  Its disadvantage is its limited coverage.  In its most
complex form, bringup.c exercises portions of the CPU core, console I/O and
file I/O.

