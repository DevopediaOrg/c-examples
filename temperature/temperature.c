/*
Temperature conversion from Celsius to Fahrenheit and vice versa.
Should be called with two arguments: temperature and unit.
Unit can be C or F.
Example arguments:
23.4 C
40.1 F
*/

#include <stdio.h>
#include <stdlib.h>

float cel_to_fah(float temp_in_C) {
    float temp_in_fah;
    temp_in_fah = (temp_in_C * 9/5) + 32;
    return temp_in_fah;
}

float fah_to_cel(float temp_in_F) {
    float temp_in_cel;
    temp_in_cel = (temp_in_F - 32) * 5/9;
    return temp_in_cel;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error: expecting exactly 2 program arguments. Quitting...\n");
        return 1;
    }
   
    float temperature = (float)atof(argv[1]);
    char unit = argv[2][0];

    // Old code to prompt for user input
    // printf("Enter temperature (C or F): ");
    // scanf("%f %c", &temperature, &unit);

    switch (unit) {
        case 'C':
            printf("%f F\n", cel_to_fah(temperature));
            break;
        case 'F':
            printf("%f C\n", fah_to_cel(temperature));
            break;
        default:
            printf("Error: unrecognized temperature unit. Only celsius or fahrenheit allowed.\n");
            break;
    }

    return 0;
}