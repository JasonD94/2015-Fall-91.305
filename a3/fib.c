/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */

#include <stdio.h>

int find_fibonacci(int n);

int main() {
    int count = 0;

    printf("First 25 Fibonacci numbers: \n\n");

    while(count <= 25) {
        printf("Fib #%d = %d\n", count, find_fibonacci(count));
        count++;
    }

    return 0;
}

// Given an int N, this function returns the given fibonacci number.
int find_fibonacci(int n) {
    int fib = 0, fib1 = 0, fib2 = 1, count = 0;

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    else if (n > 1) {

        while (count < n) {
            /*
                Formula is:
                Fn = Fn-1 + Fn-2
                Fib is Fn. Fib1 is Fn-1. Fib2 is Fn-2.
            */
            fib = fib1 + fib2;
            fib2 = fib1;            // First update fib2 so we don't lose fib1.
            fib1 = fib;             // We can then update fib1.
            count++;
        }

        return fib;     // We've got the fibonacci number that we want.
    }

    return 0;
}