/*
This code solves Project Euler Problem 40.
See https://projecteuler.net/problem=40
Expected answer is 210.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char fractional[1000000];
    int len = 0;
    for (int i = 0; i < 1000000; i++) {
        // Measure speed of execution using:
        // Windows PowerShell: Measure-Command { .\main.exe }
        // Linux Terminal: time main.exe
        
        // Slow: strlen() gets slower as string grows longer
        //len = strlen(fractional);
        //sprintf(fractional + len, "%d", i + 1);

        // Fast: make use of the return from sprintf()
        len += sprintf(fractional + len, "%d", i + 1);

        if (len >= 10000000) break;
    }

    int num = 1;
    int indices[] = { 0, 9, 99, 999, 9999, 99999, 999999 };
    for (int i = 0; i < sizeof(indices)/sizeof(int); i++) {
        num *= fractional[indices[i]] - '0';
    }
    printf("%d", num);

    return 0;
}