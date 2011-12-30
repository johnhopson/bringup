#bringup
- - - - - - - -
bringup.c is intended to be the first file compiled with a new embedded toolset
or the first file run on a new embedded target.  It doesn't require an OS, and
by default it doesn't use any I/O, however, I/O is supported with 
compile-time parameters.


### Details
bringup.c finds prime numbers from 2 to a specified maximum.  By default it
runs one cycle and exits, and is purely computational.  Console or file 
logging can be added at compile-time.  The algorithm is the 
[prime sieve of Eratosthenes](http://en.wikipedia.org/wiki/Sieve_of_eratosthenes).


### Usage

    gcc  -g  -o bringup.exe  bringup.c
      Find primes from 2 to 1000 and exit. Purely computational.  
      With debug information (-g).  No I/O.  Run as 'bringup.exe'

    gcc  -D USE_PRINTF  -o bringup.exe  bringup.c
      Find primes from 2 to 1000.  Print output to the 
      console (but not to file).  
    
    gcc  -g  -D MAX_PRIME_CANDIDATE=750  -D NUM_CYCLES=100  
         -D MEASURE_TIME  -D USE_PRINTF  -D LOG_FILE=\"bringup.log\"
         -o bringup.exe  bringup.c

      Uses all options.  Find primes from 2 to 750, 100 times, and
      exit. Print elapsed time.  Print output to console and to file 
      'bringup.log'.


### Testing
bringup_test.rb is a test suite for bringup.c.  Type 'bringup_test.rb' to run
the entire suite.  Type 'bringup_test.rb -h' to see usage, including how to 
run individual tests.


### Other
bringup.c can be used as a simple first-order benchmark.  It's advantage is
simplicity and consistency on any platform.  Comparisons are truly apples-and-
apples.  Its disadvantage is its limited coverage.  In its most complex form, 
bringup.c only exercises portions of the CPU core, console I/O and file I/O.


### License
Released under the MIT License.  See 'license' file.
