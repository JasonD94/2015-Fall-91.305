/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <stdio.h>
#include <stdlib.h>

/*  Union to use for the conversion.
    This post pointed me in the right direction:
    https://stackoverflow.com/questions/15685181/how-to-get-the-sign-mantissa-and-exponent-of-a-floating-point-number

    Also, the "convert_float_to_bits.c" file gave me some ideas as well:
    https://jeapostrophe.github.io/courses/2015/fall/305/notes/dist/convert_float_to_bits.c
*/
union float_32 {
    float float_value;
    struct {
        unsigned int mantissa: 23;
        unsigned int exponent:  8;
        unsigned int          sign:  1;
    } part;
} float_32;

// Function to convert the input into readable output.
void print_output(float output);

// Function to output to binary.
void output_binary(int integer_input);

int main(int argc, char* argv[]) {
    float input;
    int valid = 0;

    // Get input until we find a newline ('\n')
    do {
        printf("Enter a float(s): ");
        valid = scanf(" %f", &input);
        print_output(input);
    // scanf will return 1 if it gets a valid input, 0 if it gets invalid input and -1 on EOF.
    // It should separate inputs by ignoring newlines and quit whenever it hits EOF.
    } while (valid == 1);

    return 0;
}


void print_output(float output) {

    // Use the union to print out the mantissa / exponent / sign.
    float_32.float_value = output;

    // TODO: check output and compare.

    /*
        Note - decided to line the lines up correctly, so I found an easier way to do so using Stackoverflow.
        (although I'm aligning right not left)
        https://stackoverflow.com/questions/1809399/c-how-to-justify-output-lines-using-printf-to-get-equal-length
    */

    printf("The floating point value for %.1f is broken out as: \n", output);

    printf("%12s 0x%-8x %10s ", "mantissa:", float_32.part.mantissa, "or:");
    output_binary(float_32.part.mantissa);

    printf("%12s 0x%-8x %10s ", "exponent:", float_32.part.exponent, "or:");
    output_binary(float_32.part.exponent);

    printf("%12s %-10x %10s ", "sign:", float_32.part.sign, "or:");
    output_binary(float_32.part.sign);

    printf("%12s %-10f %10s ", "in base 10:", output, "or:");
    output_binary(output);

    return;
}

/*  TODO: test this function.
    Idea from this post, but I changed it to a char array to make it remove leading zeroes.
https://stackoverflow.com/questions/19823359/represent-unsigned-integer-in-binary
*/
void output_binary(int integer_input) {
    char bit_array[32];
    int x, count = 1, k = 1;

    // Initalize everything to zero.
    for (x = 0; x < 32; x++) {
        bit_array[x] = '0';
    }

    // Convert to 1s and 0s, spacing everything out in groups of 4.
    for (x = 0; x < 32; x++) {
        if (integer_input & k) {        // Bitwise AND operation.
            bit_array[x] = '1';
        }
        else {
            bit_array[x] = '0';
        }
        k = k << 1;                         // Left shift by one place each time.
    }

    // Hack: remove leading zeroes by replacing them with spaces!
    for (x = 31; x >= 0; x--) {
        if(bit_array[x] == '0') {                   // Just remove any zeroes we find!
            bit_array[x] = ' ';
        }
        else if (bit_array[x] == '1') {         // And as soon as we find a 1, quit the loop!
            break;
        }

        // But, what if we removed the only zero?
        // We better add that back in.
        if (x == 0) {
            bit_array[31] = '0';
        }
    }

    // Reverse the order of the bit array.
    for (x = 31; x >= 0; x--) {

        // HACK: don't print out spaces!
        if (bit_array[x] != ' ') {
            printf("%c", bit_array[x]);

            // This is to group the bits in groups of 4, like the example does.
            if (count == 4) {
                printf(" ");
                count = 0;
            }

            count++;
        }
    }

    printf("\n");

    return;
}