/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    // We should insure the user supplies us with at least one  floating point number.
    if (argc < 2) {

        // If they didn't enter a floating point number, we will remind them to.
        // argv[0] should be the program's name, according to Google.
        // See: http://www.cprogramming.com/tutorial/c/lesson14.html for details.
        printf("** Error - no floating point numbers entered. **\n");
        printf("Usage: %s 123.123 123.134 ...\n", argv[0]);
    }

    // If we get here, we can start doing stuff with the floating point number the user entered.
    // Let's just print it out for now to see if this works so far.
    // Seems like argv[1] to argv[argc] should be our floating point numbers.
    int x;

    /*  This will be the main loop that goes through all of the input and figures out the following:
         mantissa:
         exponent:
                  sign:

    */
    for(x = 1; x < argc; x++) {
        printf("This is what you entered: %s\n", argv[x]);
    }

    return 0;
}