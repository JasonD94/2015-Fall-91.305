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
*/
typedef union {
    float test;
    struct {
        unsigned int   mantissa: 23;
        unsigned int exponent:   8;
        unsigned int          sign:  1;
    } part;
} float_convert;

// Function to convert the input into readable output.
void print_output(float output);

// Function to output to binary.
void output_binary(unsigned int x);

int main(int argc, char* argv[]) {
    float input;
    int valid = 0;

    printf("Enter a float(s): ");

    // Get input until we find a newline ('\n')
    do {
        valid = scanf("%f", &input);
        print_output(input);
    } while (valid == 1);   // scanf will return 1 if it gets a valid input, 0 if it gets invalid input and -1 on EOF.

    //TODO: make program quit when input is done.

    return 0;
}


void print_output(float output) {

    // Use the union to print out the mantissa / exponent / sign.
    float_convert in;
    in.test = output;

    // might not need this after all.
    /*char buffer_mantissa[24];
    char buffer_exponent[9];
    char buffer_sign[2];
    char buffer_base10[33];
    */

    // TODO: check output and compare.
    // TODO: convert to binary some how.

    /*
        Note - decided to line the lines up correctly, so I found an easier way to do so using Stackoverflow.
        (although I'm aligning right not left)
        https://stackoverflow.com/questions/1809399/c-how-to-justify-output-lines-using-printf-to-get-equal-length
    */

    printf("The floating point value for %.1f is broken out as: \n", output);

    printf("%12s %-10x %10s ", "mantissa:", in.part.mantissa, "or:");
    output_binary(in.part.mantissa);        // TODO: make a function that outputs an int as binary.

    printf("%12s %-10x %10s ", "exponent:", in.part.exponent, "or:");
    output_binary(in.part.exponent);        // TODO: make a function that outputs an int as binary.

    printf("%12s %-10x %10s ", "sign:", in.part.sign, "or:");
    output_binary(in.part.sign);        // TODO: make a function that outputs an int as binary.

    printf("%12s %-10f %10s ", "in base 10:", output, "or:");
    output_binary(output);        // TODO: make a function that outputs an int as binary.

    return;
}

// TODO: write this function.
void output_binary(unsigned int x) {

    printf("100 0000 0000\n");
}