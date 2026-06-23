/*
Find the sum of the first 10 terms of convergent series, 1 + 2/7 + 3/7^2 + ...
*/

#include <stdio.h>
#include <math.h>

int main() {
    double sum = 0;

    for (int i = 0; i < 10; i++) {
        sum += (i + 1) / pow(7, i);
    }

    printf("Sum is %.6f\n", sum);

    return 0;
}