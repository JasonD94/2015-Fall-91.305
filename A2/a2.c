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

// Function to add two floating point numbers using integer addition.
float add_floating_point(float first_int, float second_int);


int main() {

    float float1, float2, hardware, emulated;
    int valid = 1;

    // Get input until input stops.
    do {
        // Float 1
        valid = scanf("%f", &float1);

        if (valid == 0 || valid == -1) {            // scanf will return 0 if it gets invalid input and -1 on EOF.
            break;
        }

        print_output(float1, 1);

        // Float 2
        valid = scanf("%f", &float2);

        if (valid == 0 || valid == -1) {            // scanf will return 0 if it gets invalid input and -1 on EOF.
            break;
        }

        print_output(float2, 2);

        // Output the "Hardware" section
        hardware = float1 + float2;
        print_output(hardware, 3);

        // Output the "Emulated" section
        emulated = add_floating_point(float1, float2);
        print_output(emulated, 4);

    // scanf will return 1 if it gets a valid input, 0 if it gets invalid input and -1 on EOF.
    } while (valid == 1);

    return 0;
}


// Function to convert the input into readable output.
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
        printf("\n");
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

                // Prevent trailing whitespace by catching when y == 0.
                // This messed up my diff command.
                if( (count == 4) &&  (y != 0) ) {                            // Catch groups of 4 by counting to 4.
                    printf(" ");
                    count = 0;
                }

                count++;
            }
        }
    }

    return;
}


// Function to add two floating point numbers using integer addition.
float add_floating_point(float first_int, float second_int) {

    int first_man = 0, second_man = 0, first_exp = 0, second_exp = 0, first_sign = 0, second_sign = 0;
    int sum = 0, count = 0;

    // Split the two floating point numbers into their integer parts, mantissa / exponent / sign
    float_32.float_value = first_int;
    first_man = float_32.part.mantissa;                 // Split the first float
    first_exp = float_32.part.exponent;
    first_sign = float_32.part.sign;

    float_32.float_value = second_int;
    second_man = float_32.part.mantissa;            // Split the second float
    second_exp = float_32.part.exponent;
    second_sign = float_32.part.sign;

    // First let's check and see if we can add these two numbers without overflowing / underflowing.

    // let's output all this for debugging.
    //printf("\nFirst float: %d %d %d\n", first_man, first_exp, first_sign);
    //printf("\nSecond float: %d %d %d\n", second_man, second_exp, second_sign);

    /*
            Adjust the exponents so that they are equal.
            We will do this by incrementing the smaller exponent until it is equal to the larger exponent.
            We also need to adjust the mantissa when we do this, and we adjust right by 1 to do so.
    */

    // Adjust the first exponent (and mantissa) since it is smaller.
    if (first_exp < second_exp) {

        while (first_exp != second_exp) {
            first_man = first_man >> 1;                                     // Right shift by 1.
            first_exp++;
            count++;
        }
    }

    // Adjust the second exponent (and mantissa) since it is smaller.
    if (first_exp > second_exp) {

        while (first_exp != second_exp) {
            second_man = second_man >> 1;                            // Right shift by 1.
            second_exp++;
            count++;
        }
    }

    /* The two exponents are equal now, so we can move on to adding the mantissas.
        The bit shift at the end is to add 2 ^ 23 - count, which should add the hidden bit back in.
        This is because I count how many times I shift , and then add the missing bit back in at
        that given location.
        So far this works for the first input. Need to test on more inputs to see if this is valid or not.

        Idea to bit shift to do the pow came from this post:
       https://stackoverflow.com/questions/7458072/how-to-use-raise-to-the-power-of-x-in-c
    */
    sum = first_man + second_man + (1 << (23 - count));

    // Determine the sign of the final floating point number.
    if (sum > 0) {
        float_32.part.sign = 0;
    }
    else {
        float_32.part.sign = 1;
    }

    // Construct the rest of the final floating point number.
    float_32.part.mantissa = sum;                 // The sum of the two mantissas.
    float_32.part.exponent = first_exp;         // These should be the same so it doesn't matter which one we use.

    // let's output all this for debugging.
    //printf("\nFirst float: %d %d %d\n", first_man, first_exp, first_sign);
    //printf("\nSecond float: %d %d %d\n", second_man, second_exp, second_sign);

    // Return the final float value.
    return float_32.float_value;
}