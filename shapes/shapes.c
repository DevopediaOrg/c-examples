/*
A few examples to practice handling of strings and printf().
In these examples we print various shapes of letters or digits.
*/

#include <stdio.h>

/*
a
ab
abc
abcd
abcde
abcdef
*/
void abcdef() {
    char data[] = "abcdef";
    char excess[sizeof(data)] = {};

    for (int i = 0; i < 6; i++) {
        excess[i] = data[i];
        printf("%s\n", excess);
    }
}

/*
        9
       898
      78987
     6789876
    567898765
   45678987654
  3456789876543
 234567898765432
12345678987654321
*/
void numbers() {
    // In this code, we treats the digits as char, not int
    char data[] = "12345678987654321";

    for (int i = 0; i < 9; i++) { // 0-indexed row num
        for (int j = -i; j < i+1; j++) { // loop for number of chars in row
            // Example: 898: i==1 and j is [-1, 0, 1]
            if (j == -i) {
                // for first char in row add left padding
                char format[4];
                sprintf(format, "%%%dc\0", 9+j);
                printf(format, data[8+j]);
            }
            else printf("%c", data[8+j]);
        }
        printf("\n");
    }
}

/*
   A
  B B
 C   C
D     D
 E   E
  F F
   G
*/
void diamond() {
    // This implementation uses the symmetry around 'D'
    // The beauty of this code is 'center' variable can be
    // and the rest of the code will work.
    char center = 'D';
    int depth = center - 'A';
    for (int i = -depth; i <= depth; i++) {
        /*
         i  spaces  letter  spaces   letter
        -3  3       A               
        -2  2       B       1        B
        -1  1       C       3        C
         0  0       D       5        D
         1  1       E       3        E
         2  2       F       1        F
         3  3       G
        */
        int abs_val = i < 0 ? -i : i; // get absolute value, or call abs() of math.h
        char format[5];
        
        sprintf(format, "%%%dc\0", abs_val+1);
        printf(format, center + i);

        if (abs_val != depth) {
            sprintf(format, "%%%dc\0", 2*(depth-1-abs_val)+2);
            printf(format, center + i);
        }
        printf("\n");
    }
}


int main() {
    abcdef();
    printf("\n\n");

    numbers();
    printf("\n\n");

    diamond();
    printf("\n\n");

    return 0;
}
