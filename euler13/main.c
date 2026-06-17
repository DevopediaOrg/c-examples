/*
This code solves Project Euler Problem 13.
See https://projecteuler.net/problem=13
Expected answer is 5537376230.
Input data filename is hardcoded below.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_INTS 100
#define INT_LEN 50


int main() {
    char data[NUM_INTS][INT_LEN+2]; // \n and \0 at the end

    FILE *fp = fopen("euler13.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open data file. Quitting...\n");
        return 1;
    }

    for (int i = 0; i < NUM_INTS; i++) {
        fgets(data[i], INT_LEN + 2, fp);
        data[i][INT_LEN] = '\0'; // overwrite \n
        printf("%2d %s\n", i, data[i]);
    }

    unsigned int carryover = 0;
    char full_sum[2+INT_LEN+1] = {};
    for (int j = 0; j < INT_LEN / 5; j++) {
        // In this loop, process only 5 digits per iteration.
        // Start processing from rightmost digits and save
        // carryover for next iteration.
        unsigned int sum = carryover;
        unsigned int offset = INT_LEN - (j+1)*5;
        for (int i = 0; i < NUM_INTS; i++) {
            // In this loop, add 5 digits of all NUM_INTS integers.
            char numstr[5+1] = {};
            strncpy(numstr, data[i] + offset, 5);
            sum += atoi(numstr);
        }
        char sumstr[2+5+1] = {};
        snprintf(sumstr, 2+7+1, "%07u", sum);
        strncpy(full_sum + 2 + offset, sumstr + 2, 5);
        sumstr[2] = '\0'; // retain only 2 leftmost digits
        carryover = atoi(sumstr);
    }

    // Final carryover
    char co_str[2+1] = {};
    snprintf(co_str, 2+1, "%02u", carryover);
    strncpy(full_sum, co_str, 2);

    printf("Sum (%d digits): %s\n", strlen(full_sum), full_sum);
    full_sum[10] = '\0'; // retain only 10 leftmost digits
    printf("Sum (first 10 digits): %s\n", full_sum);

    return 0;
}