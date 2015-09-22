/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <stdio.h>
#include <stdlib.h>

/*
    Union to use for the conversion.
    This post pointed me in the right direction:
    https://stackoverflow.com/questions/15685181/how-to-get-the-sign-mantissa-and-exponent-of-a-floating-point-number

    Also, the "convert_float_to_bits.c" file gave me some ideas as well:
    https://jeapostrophe.github.io/courses/2015/fall/305/notes/dist/convert_float_to_bits.c
*/
typedef union float_32 {
    float float_value;
    struct {
        unsigned int mantissa: 23;
        unsigned int exponent:  8;
        unsigned int          sign:  1;
    } part;
    struct single_bits {
      unsigned  b0 :1;              // Sign
      unsigned  b1 :1;              // Exponent
      unsigned  b2 :1;
      unsigned  b3 :1;
      unsigned  b4 :1;
      unsigned  b5 :1;
      unsigned  b6 :1;
      unsigned  b7 :1;
      unsigned  b8 :1;
      unsigned  b9 :1;              // Mantissa
      unsigned  b10:1;
      unsigned  b11:1;
      unsigned  b12:1;
      unsigned  b13:1;
      unsigned  b14:1;
      unsigned  b15:1;
      unsigned  b16:1;
      unsigned  b17:1;
      unsigned  b18:1;
      unsigned  b19:1;
      unsigned  b20:1;
      unsigned  b21:1;
      unsigned  b22:1;
      unsigned  b23:1;
      unsigned  b24:1;
      unsigned  b25:1;
      unsigned  b26:1;
      unsigned  b27:1;
      unsigned  b28:1;
      unsigned  b29:1;
      unsigned  b30:1;
      unsigned  b31:1;
    } bit;
} float_32;

void print_output(float output, int num);                                                  // Function to convert the input into readable output.
void output_binary(int integer_input, int bits);                                         // Function to output to binary.
float add_floating_point(float_32 first_int, float_32 second_int);      // Add two floating point numbers

int main() {
    float float1, float2, hardware, emulated;
    float_32 float_1, float_2;
    int valid = 1;

    do {
        valid = scanf("%f", &float1);               // Float 1

        if (valid == 0 || valid == -1) {            // scanf will return 0 if it gets invalid input and -1 on EOF.
            break;
        }

        print_output(float1, 1);

        valid = scanf("%f", &float2);               // Float 2

        if (valid == 0 || valid == -1) {            // scanf will return 0 if it gets invalid input and -1 on EOF.
            break;
        }

        print_output(float2, 2);

        hardware = float1 + float2;                // Output the "Hardware" section
        print_output(hardware, 3);

        float_1.float_value = float1;
        float_2.float_value = float2;

        emulated = add_floating_point(float_1, float_2);              // Output the "Emulated" section
        print_output(emulated, 4);

    } while (valid == 1);                               // scanf will return 1 if it gets a valid input, 0 if it gets invalid input and -1 on EOF.

    return 0;
}

// Function to output floating point values as binary output
void print_output(float output, int num) {
    float_32 output_float;
    output_float.float_value = output;                 // Use the union to print out the mantissa / exponent / sign.

    if(num == 1 || num == 2) {
        printf(" Float %d: %.6f\n", num, output);           // Float 1 / Float 2 output
        printf("          bits: ");

        printf("%x ", output_float.part.sign);
        output_binary(output_float.part.exponent, 8);           // Binary output
        output_binary(output_float.part.mantissa, 23);
        printf("\n");
    }
    else if(num == 3) {                                                  // Hardware output section
        printf("Hardware: %.6f\n", output);
        printf("          bits: ");

        printf("%x ", output_float.part.sign);                          // Binary output
        output_binary(output_float.part.exponent, 8);
        output_binary(output_float.part.mantissa, 23);
        printf("\n");
    }
    else if(num == 4) {                                                  // Emulated output section
        printf("Emulated: %.6f\n", output);
        printf("          bits: ");

        printf("%x ", output_float.part.sign);                          // Binary output
        output_binary(output_float.part.exponent, 8);
        output_binary(output_float.part.mantissa, 23);
        printf("\n\n");
    }
}

// This function prints out a binary number given an integer.
void output_binary(int integer_input, int bits) {
    int bit_array[32];
    int x, y, count = 1;

    for (x = 0; x < 32; x++) {                        // Initalize everything to zero.
        bit_array[x] = 0;
    }

    for (x = 0; integer_input > 0; x++) {        // Convert to binary
        bit_array[x] = integer_input % 2;          // Place the remainder in the bit_array
        integer_input = integer_input / 2;          // Continue dividing by 2 until divide is equal to zero.
    }

    if (bits == 8) {                                            // Exponent stuff
        for (y = 7; y >= 0; y--) {
            printf("%d", bit_array[y]);

            if(count == 4) {                                  // Catch groups of 4 by counting to 4.
                printf(" ");
                count = 0;                                        // Equal to 0 since count will be incremented right after.
            }

            count++;
        }
    }

    if (bits == 23) {                                       // Mantissa stuff
        count = 2;                                            // fix the first group of 4 being wrong.

        for (y = 22; y >= 0; y--) {
            if(y > 19) {                                      // Output the group of 3
                printf("%d", bit_array[y]);
            }
            else if (y == 19) {                          // Separate the group of 3 by a space.
                printf(" %d", bit_array[y]);
            }
            else {                                               // This part is either the rest of the mantissa.
                printf("%d", bit_array[y]);

                // Prevent trailing whitespace by catching when y == 0 -- This messed up my diff command.
                if( (count == 4) &&  (y != 0) ) {
                    printf(" ");                                        // Catch groups of 4 by counting to 4.
                    count = 0;
                }

                count++;
            }
        }
    }
}

// Function to add two floating point numbers using integer addition.
float add_floating_point(float_32 first_int, float_32 second_int) {
    int counter = 0;
    float_32 float_sum;         // Hold the sum of the two floating point numbers

    // No need to adjust since the exponents are the same.
    if (first_int.part.exponent == second_int.part.exponent) {
        float_sum.part.exponent = first_int.part.exponent;         // Just use the first exponent.
    }

    // Adjust the first mantissa since it is smaller. The 2nd exponent will be used.
    else if (first_int.part.exponent < second_int.part.exponent) {

        // Get the amount to shift by. Only shift to the right.
        counter = second_int.part.exponent - first_int.part.exponent;

        // Right shift once, then put the hidden bit in that spot.
        first_int.part.mantissa  >>= 1;                                                         // Short hand for val = val >> 1

        // Put the hidden bit in place of the zero we just shifted in.
        first_int.bit.b22 = 1;

        // Need to decrement the shift counter now if it isn't equal to zero.
        if (counter > 0) {
            counter--;
        }

        first_int.part.mantissa  >>= counter;                                               // Shift right by the shift amount.
        float_sum.part.exponent = second_int.part.exponent;                    // Second exponent was larger so use this one.
    }

    // Adjust the second mantissa since it is smaller. The 1st exponent will be used.
    else if (first_int.part.exponent > second_int.part.exponent) {

        // Get the amount to shift by. Only shift to the right.
        counter = first_int.part.exponent - second_int.part.exponent;

        // Right shift once, then put the hidden bit in that spot.
        second_int.part.mantissa  >>= 1;                                                         // Short hand for val = val >> 1

        // Put the hidden bit in place of the zero we just shifted in.
        second_int.bit.b22 = 1;

        // Need to decrement the shift counter now if it isn't equal to zero.
        if (counter > 0) {
            counter--;
        }

        second_int.part.mantissa  >>= counter;          // Shift right by the shift amount.
        float_sum.part.exponent = first_int.part.exponent;                                    // first exponent was larger so use this one.
    }

    // Add the two mantissas together.
    float_sum.part.mantissa = first_int.part.mantissa + second_int.part.mantissa;

    return float_sum.float_value;                // Return the final float value.
}