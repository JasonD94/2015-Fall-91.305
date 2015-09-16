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
void print_output(float output, int num);

// Function to output to binary.
void output_binary(int integer_input, int bits);


int main() {

    float float1, float2, sum;
    int valid = 1;

    // Get input until input stops.
    do {
        // Float 1
        valid = scanf("%f", &float1);

        if (valid == 0 || valid == -1) {             // scanf will return 0 if it gets invalid input and -1 on EOF.
            break;
        }

        print_output(float1, 1);

        // Float 2
        valid = scanf("%f", &float2);

        if (valid == 0 || valid == -1) {            // scanf will return 0 if it gets invalid input and -1 on EOF.
            break;
        }

        print_output(float2, 2);

        sum = float1 + float2;

        // Output the "Hardware" section
        print_output(sum, 3);

        // Output the "Emulated" section
        print_output(sum, 4);

    // scanf will return 1 if it gets a valid input, 0 if it gets invalid input and -1 on EOF.
    } while (valid == 1);

    return 0;
}


void print_output(float output, int num) {

    float_32.float_value = output;              // Use the union to print out the mantissa / exponent / sign.

    // Float 1 / Float 2 output
    if(num == 1 || num == 2) {
        printf(" Float %d: %.6f\n", num, output);
        printf("          bits: ");

        // Binary output
        printf("%x ", float_32.part.sign);
        output_binary(float_32.part.exponent, 8);
        output_binary(float_32.part.mantissa, 23);
        printf("\n");
    }

    // Hardware output section
    else if(num == 3) {
        printf("Hardware: %.6f\n", output);
        printf("          bits: ");

        // Binary output
        printf("%x ", float_32.part.sign);
        output_binary(float_32.part.exponent, 8);
        output_binary(float_32.part.mantissa, 23);
        printf("\n");
    }

    // Emulated output section
    else if(num == 4) {
        printf("Emulated: %.6f\n", output);
        printf("          bits: ");

        // Binary output
        printf("%x ", float_32.part.sign);
        output_binary(float_32.part.exponent, 8);
        output_binary(float_32.part.mantissa, 23);
        printf("\n\n");
    }

    return;
}


/*
        This function prints out a binary number given an integer.
        I have it setup to space out the mantissa and the exponent in groups of 3 or 4, like the
        example given does.
*/
void output_binary(int integer_input, int bits) {
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

    // Exponent stuff
    if (bits == 8) {
        for (y = 7; y >= 0; y--) {
            printf("%d", bit_array[y]);

            if(count == 4) {                                // Catch groups of 4 by counting to 4.
                printf(" ");
                count = 0;                                      // Equal to 0 since count will be incremented right after.
            }

            count++;
        }
    }

    // Mantissa stuff
    if (bits == 23) {
        count = 2;                  // fix the first group of 4 being wrong.

        for (y = 22; y >= 0; y--) {
            if(y > 19) {                                      // Output the group of 3
                printf("%d", bit_array[y]);
            }
            else if (y == 19) {                          // Separate the group of 3 by a space.
                printf(" %d", bit_array[y]);
            }
            else {                                                 // This part is either the rest of the mantissa.
                printf("%d", bit_array[y]);

                if(count == 4) {                            // Catch groups of 4 by counting to 4.
                    printf(" ");
                    count = 0;
                }

                count++;
            }
        }
    }

    return;
}
