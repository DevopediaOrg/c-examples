/*
This program estimates the value of pi using Monte Carlo simulation.
See https://en.wikipedia.org/wiki/Monte_Carlo_method
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10000000

int main() {
    int inside = 0;

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        double r = sqrt(pow(x, 2) + pow(y, 2));
        if (r < 1) inside++;
    }

    // Area of quarter circle / Area of square = 
    // = (pi * 1^2 / 4) / 1^2 = inside / N
    // => pi = 4 * inside / N
    printf("Value of pi is %.2f\n", 4.0 * inside / N);

    return 0;
}