/*
This code solves Project Euler Problem 19.
See https://projecteuler.net/problem=19
Expected answer is 171.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    NumOfDays
} DayOfWeek;


int is_leap_year(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
}


int main() {
    int days_in_month[12] = { 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int num_sunday_start = 0;

    // 1-Jan-1900 is Monday, find day on 1-Jan-1901
    DayOfWeek today = (Monday + (365 % 4)) % NumOfDays;

    for (int year = 1901; year <= 2000; year++) {
        days_in_month[1] = is_leap_year(year) ? 29 : 28;
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < days_in_month[i]; j++) {
                today = (today + 1) % NumOfDays;
                if (j ==0 && today == Sunday) num_sunday_start++;
            }
        }
    }

    printf("%d", num_sunday_start);

    return 0;
}