# bringup.c

## What is bringup.c?
bringup.c is intended to be the first file compiled with a new embedded toolset
or the first file run on a new embedded target.  Its value is that it can be
purely computational (no I/O), or simple I/O can be added with a few compile-
time definitions.

## What does bringup.c do?
bringup.c finds prime numbers from 2 to a specified maximum.  By default, it
uses no I/O, but it can print data to the console and/or a file.  The algorithm
is the [prime sieve of Eratosthenes](http://en.wikipedia.org/wiki/Sieve_of_eratosthenes).

## How else can I use bringup.c?
bringup.c can be used as a simple first-order benchmark.  It has the advantage
of being simple to configure, so the user has confidence that comparisons are
truly apples-to-apples.  The disadvantage is its limited coverage.  In its most
complex form, bringup.c exercises the CPU core, console I/O and file I/O.  That
may or may not be a sufficient test, but it is a good first-order indicator.

