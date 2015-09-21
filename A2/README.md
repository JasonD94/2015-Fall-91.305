DIY Floating Point Addition
===========================
This program will read two 32 bit floating point numbers from standard input
and it will add them together using C's integer operations.

The output of the program will look exactly like:

```
 Float 1: 34.500000
          bits: 0 1000 0100 000 1010 0000 0000 0000 0000
 Float 2: 1.250000
          bits: 0 0111 1111 010 0000 0000 0000 0000 0000
Hardware: 35.750000
          bits: 0 1000 0100 000 1111 0000 0000 0000 0000
Emulated: 35.750000
          bits: 0 1000 0100 000 1111 0000 0000 0000 0000
 ```

 #TODO
 1. Test output
 2. Fix "inf" on last given test input
 3. Find more input numbers to test against.