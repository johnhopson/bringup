#bringup

---

<<<<<<< HEAD
### What is bringup.c?
=======
## What is bringup.c?
>>>>>>> Changed OUTPUT_FILE to LOG_FILE
bringup.c is intended to be the first file compiled with a new embedded toolset
or the first file run on a new embedded target.  Its value is that it can be
purely computational (no I/O), and yet I/O can be easily added at compile time.

### What does it do?
bringup.c finds prime numbers from 2 to a specified maximum.  By default, it
is purely computational, using only the CPU core, but it can be configured to
print data to the console and/or to a log file.  The algorithm is the 
[prime sieve of Eratosthenes](http://en.wikipedia.org/wiki/Sieve_of_eratosthenes).

### How do I compile it?
Here are some example builds

    gcc  -o bringup.exe  bringup.c

        Find primes from 2 to 1000 and exit. Purely computational.  Uses no I/O.
    
    gcc  -D NUM_CYCLES=0  -D USE_PRINTF  -o bringup.exe  bringup.c

        Find primes from 2 to 1000.  Run forever until stopped.  Print output 
        to the console (but not to file).  
    
    gcc  -D MAX_PRIME_CANDIDATE=750  -D NUM_CYCLES=100  -D MEASURE_TIME
         -D USE_PRINTF  -D LOG_FILE=\"bringup.log\"
         -o bringup.exe  bringup.c

        Uses all options.  Find primes from 2 to 750, 100 times, and exit.  
        Print elapsed time before exit.  Print output to console and to file 
        'bringup.log'.

### What else does it do?
bringup.c can be used as a simple first-order benchmark.  It's advantage is
simple and consistent configuration on any platform, so comparisons are truly
apples-and-apples.  Its disadvantage is its limited coverage.  In its most
complex form, bringup.c exercises portions of the CPU core, console I/O and
file I/O.  That may or may not be sufficient, but it is a good first-order 
speed indication.

