/*
This code takes an array of strings and returns the longest one.
*/

#include <stdio.h>
#include <string.h>


char *maxstr(char *data[], int len) {
    int maxlen = strlen(data[0]);
    char *maxstr = data[0];
    for (int i = 1; i < len; i++) {
        int len = strlen(data[i]);
        if (len > maxlen) {
            maxlen = len;
            maxstr = data[i];
        }
    }
    return maxstr;
}

int main() {
    char *data[] = { // array of pointers to strings
        "Chennai",
        "New York",
        "San Francisco",
        "London",
        "Bangalore",
        "Tokyo"
    };
    int len = sizeof(data) / sizeof(data[0]);
    printf("Maximum string is %s\n", maxstr(data, len));
}