# Assignment 1 - Floating Point Representation

Assignment 1 for Computer Architecture.

This programs reads any number of floating point numbers from standard input, and outputs the following information:

mantissa

exponent

sign

base 10 equivalent

Approach
======
I used a union to get the mantissa, exponent and sign, as I included a struct with several unsigned integers inside of the union.
This works as the union stores things in the same memory space, so getting the mantissa / exponent / sign were relatively
easy with this approach. The tricky part was getting the output looking correct and converting the mantissa / exponent to
binary. Since C doesn't have a standard int / float to binary function I created two functions to handle the output / binary
conversion.

void print_output(float output);
------------------------------------------

This function made it easier to output the mantissa / exponent / sign / base 10 equivalent. It also contains the alignment
code which makes all the values line up nicely, either left aligned or right aligned depending on the column.

void output_binary(int integer_input, int bits);
--------------------------------------------------

I made an int to binary conversion function since C doesn't apparently have one built in. A stackoverflow post gave me
the idea for the function, since itoa (http://www.cplusplus.com/reference/cstdlib/itoa/) isn't valid ANSI-C. Although I ended up
just doing a standard binary conversion, divide by 2 and check the remainder until you hit 0. I also added the "int bits" part
in order to print out the mantissa and the exponent correctly. It is a bit of a hack but it works and I couldn't figure out how
to just figure out whether its the mantissa or the exponent in the function without passing an extra int showing how many
bits to print out.

The main issue I ran into was that leading zeros would not print out and if the number had all 1's it also
would randomly break the output. This approach seems to work and the output looks valid. I also created a test file
called test.out which uses numers from the following IEEE 754 calculators:

(Main calculator used)[http://www.h-schmidt.net/FloatConverter/IEEE754.html]

(This one was a good alternate to check against)[http://babbage.cs.qc.edu/courses/cs341/IEEE-754.html]

Testing
========================
./a1 < test.in

Or just run "make", which will run against a series of tests that I created.

To get output into a file, run this command:
./a1 < test.in > standard_output.out

NOTE
====
One of the test cases just doesn't work for some reason. I manually compared 1.0 to the online calculator and it seems to be
correct. I think there's just an issue with outputting an extra "enter a float" but I'm not really sure.