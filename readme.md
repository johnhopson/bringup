bringup.c
---------
A simple program to bring up first-article microcontroller boards or to
test the compiler/debugger toolchains to which they are attached.


### Details
In its simplest form, this program is purely computational.  It requires no
OS and not even any I/O, making it useful for establishing the
compiler/debugger/CPU path.  Once that path is established, bringup can add
printf and file I/O for further testing.

The algorithm simply finds prime numbers from 2 to a specified maximum.  It
uses the [Sieve of Eratosthenes](http://en.wikipedia.org/wiki/Sieve_of_eratosthenes).

Compile time options may be used to run multiple calculation cycles, or add
printf or file I/O.

bringup.c can also be used as a simple first-order benchmark.  It's advantage
is its simplicity and consistency on any platform.  Comparisons are truly
apples-to-apples.  Its disadvantage is its limited coverage.  In its most
complex form, bringup.c only exercises portions of the CPU core, console
I/O and file I/O.


### Usage

    gcc  -g  -o bringup.exe  bringup.c
      Run as 'bringup.exe'.  Find primes from 2 to 1000 and exit.
      No I/O.  Purely computational.  Has debug information (-g).

    gcc  -D USE_PRINTF  -o bringup.exe  bringup.c
      Find primes from 2 to 1000 and exits.  Print primes to the
      console (but not to file).

    gcc  -g  -D MAX_PRIME_CANDIDATE=750  -D NUM_CYCLES=100
         -D MEASURE_TIME  -D USE_PRINTF  -D LOG_FILE=\"bringup.log\"
         -o bringup.exe  bringup.c

      Uses all options.  Find primes from 2 to 750, 100 times, and
      exit. Print elapsed time.  Print output to console and to file
      'bringup.log'.

gcc is not required.  bringup.c should be portable to any C compiler.

### Test
test/bringup_test.rb is a test suite for bringup.c.  To run the suite, cd to
'test' and type './bringup_test.rb' to run the suite.  Type
'./bringup_test.rb -h' to see usage, including how to run individual tests.


### Other
Written and tested with Ruby 1.8.7 on OS X 10.7.

[![CC](http://i.creativecommons.org/l/by-sa/3.0/88x31.png)](http://creativecommons.org/licenses/by-sa/3.0/)   &nbsp;Licensed under [Creative Commons](http://creativecommons.org/licenses/by-sa/3.0/)
