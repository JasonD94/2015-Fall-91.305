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


int main() {

    float input;
    int valid = 0;

    // Get input until we find a newline ('\n')
    do {
        //printf("Enter a float(s): ");
        valid = scanf(" %f", &input);

        // Make sure the user didn't enter invalid input.
        // scanf will return 0 if it gets invalid input and -1 on EOF.
        if (valid == 0 || valid == -1) {
            break;
        }

        print_output(input);

    // scanf will return 1 if it gets a valid input, 0 if it gets invalid input and -1 on EOF.
    } while (valid == 1);

    return 0;
}


//  TODO: check output and compare.
void print_output(float output) {

    float_32.float_value = output;              // Use the union to print out the mantissa / exponent / sign.

    /*
            Note - I decided to line the lines up correctly, so I found an easier way to do so using Stackoverflow.
            (although I'm aligning both right and left at spots, depending how I want the output to look exactly.)
            https://stackoverflow.com/questions/1809399/c-how-to-justify-output-lines-using-printf-to-get-equal-length
    */

    printf("The floating point value for %.1f is broken out as: \n", output);

    // Mantissa
    printf("%12s 0x%-8x %10s %11s", "mantissa:", float_32.part.mantissa, "or: ", " ");
    output_binary(float_32.part.mantissa);

    // Exponent
    printf("\n%12s 0x%-8x %10s %1s", "exponent:", float_32.part.exponent, "or: ", " ");
    output_binary(float_32.part.exponent);

    // Sign
    printf("\n%12s %-10x %9s %x\n", "sign:", float_32.part.sign, "or:", float_32.part.sign);

    // In base 10
    printf("%12s %-10f %10s", "in base 10:", output, "or: ");
    printf ("%x ", float_32.part.sign);
    output_binary(float_32.part.exponent);
    output_binary(float_32.part.mantissa);
    printf("\n\n");

    return;
}


/*
        This function prints out a binary number given an integer.
        I have it setup to space out the mantissa and the exponent in groups of 3 or 4, like the
        example given does.
*/
void output_binary(int integer_input) {
    int bit_array[32];
    int x, y, count = 1;

    // Initalize everything to zero.
    for (x = 0; x < 32; x++) {
        bit_array[x] = 0;
    }

    // Convert to binary
    for (x = 0; integer_input > 0; x++) {
        bit_array[x] = integer_input % 2;          // Place the remainder in the bit_array
        integer_input = integer_input / 2;          // Continue dividing by 2 until divide is equal to zero.
    }

    // This fixes the outputting of the exponent not being lined up right.
    if (x-1 == 7) {
        count = 1;
    }
    else {
        count = 2;
    }

    // Reverse the order of the bit array, since we recorded the binary number in the opposite order
    for (y = x - 1; y >= 0; y-- ) {
        if(y > 19) {                                // If this is the mantissa, then output as a group of 3, then groups of 4.
            printf("%d", bit_array[y]);
        }
        else if (y == 19) {                     // Separate the group of 3 (assuming this is the mantissa).
            printf(" %d", bit_array[y]);
        }
        else {                                          // This part is either the rest of the mantissa or the exponent.
            printf("%d", bit_array[y]);

            if(count == 4) {                     // Catch groups of 4 by counting to 4.
                printf(" ");
                count = 0;
            }

            count++;
        }
    }

    return;
}