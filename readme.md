#bringup
- - - - - - - -
This is a simple program used to bring up a first-article microcontroller
board or to test the compiler/debugger toolchain to which it is attached.


### Details
In its simplest form, this program is purely computational.  It requires no
OS and not even any I/O, making it useful for establishing the
compiler/debugger/CPU path.  Once that path is established, bringup can add
printf and file I/O for further testing.

The algorithm simply finds prime numbers from 2 to a specified maximum.  It
uses the prime [sieve of Eratosthenes](http://en.wikipedia.org/wiki/Sieve_of_eratosthenes).

Compile time options may be used to run multiple calculation cycles, or add
printf or file I/O.


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


### Testing
test/bringup_test.rb is a test suite for bringup.c.  To run the suite, cd to
'test' and type './bringup_test.rb' to run the suite.  Type
'./bringup_test.rb -h' to see usage, including how to run individual tests.


### Other
bringup.c can be used as a simple first-order benchmark.  It's advantage is
simplicity and consistency on any platform.  Comparisons are truly apples-and-
apples.  Its disadvantage is its limited coverage.  In its most complex form,
bringup.c only exercises portions of the CPU core, console I/O and file I/O.


### Source
bringup is hosted at [github.com/johnhopson/bringup](http://github.com/johnhopson/bringup).
It is released under the MIT license.  See 'license' file.
