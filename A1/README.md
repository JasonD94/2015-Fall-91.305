# Assignment 1 - Floating Point Representation

Assignment 1 for Computer Architecture.

This programs reads any number of floating point numbers from standard input, and outputs the following information:
mantissa
exponent
sign
base 10 equivalent

I used a union to get the mantissa, exponent and sign, as I included a struct with several unsigned integers inside of the union.

There are two functions I created to make the program easy to read:

void print_output(float output);

This function made it easier to output the mantissa / exponent / sign / base 10 equivalent. It also contains the alignment
code which makes all the values line up nicely, either left aligned or right aligned depending on the column.

void output_binary(int integer_input);

I made an int to binary conversion function since C doesn't apparently have one built in. A stackoverflow post gave me
the idea for the function, since itoa (http://www.cplusplus.com/reference/cstdlib/itoa/) isn't valid ANSI-C. I also added some
spacing so that the bits are grouped by 4s and I also removed the leading zeros from the output.

TODO:

1. Test program against 10 numbers, including the following:
237.75
-.0000005126
-92457321.670245
6.023E+23
1.67339E-40

Test by running the following command:
./a1 < test.in

To get output into a file, run this command:
./a1 < test.in > standard_output.out
