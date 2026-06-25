/*
This code solves Project Euler Problem 19.
See https://projecteuler.net/problem=19
Expected answer is 171.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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


bool is_leap_year(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
}


int main() {
    int days_in_month[12] = { 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int num_sunday_start = 0;

    // 1-Jan-1900 is Monday, find day on 1-Jan-1901
    // 1900 is not a leap year, hence add only 365
    DayOfWeek today = (Monday + 365) % NumOfDays;

    for (int year = 1901; year <= 2000; year++) {
        days_in_month[1] = is_leap_year(year) ? 29 : 28;
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < days_in_month[i]; j++) {
                if (j == 0 && today == Sunday) num_sunday_start++;
                today = (today + 1) % NumOfDays;
            }
        }
    }

    printf("%d", num_sunday_start);

    return 0;
}