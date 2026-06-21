/*
A few examples to practice handling of strings and printf().
In these examples we print various shapes of letters or digits.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>


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

    // Solution 1: each digit is printed separately,
    // first digit is printed with extra left spaces
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

    // Solution 2: all digits in a row are printed together
    // along with extra left spaces
    for (int i = 0; i < 9; i++) {
        /*
        i   #spaces  #digits   #chars   format
            8-i      2*i+1     i+9
        0 : 8        1         8        %9s\n
        1 : 7        3         7        %10s\n
        2 : 6        5         6        %11s\n
        */
        char num[sizeof(data)] = {};
        strncpy(num, data + 8 - i, 2*i + 1);

        char format[6] = {};
        sprintf(format , "%%%ds\n", i + 9);
        printf(format, num);
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
    // Solution 1: We use the symmetry around 'D'.
    // The beauty of this code is 'center' variable can be
    // and the rest of the code will work.
    char center = 'D';
    int depth = center - 'A';
    for (int i = -depth; i <= depth; i++) {
        /*
         i  #spaces letter  #spaces  letter
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

    // Solution 2: Use formulae for left and center spaces
    // len/2 points to widest part of the diamond
    // abs(len/2-i) measures the distance from the widest part
    // We can add more chars to data[] and this code will still work
    char data[]="ABCDEFG";
    int len = strlen(data);

    for (int i = 0; i < len; i++) {
        // Left spaces
        for (int s = 0; s < abs(len/2-i); s++) {
            printf(" ");
        }

        if (i != 0 && i != len-1) {
            printf("%c", data[i]);
        }

        // Center spaces
        for (int s = 0; s < len-2-2*abs(len/2-i); s++) {
            printf(" ");
        }

        printf("%c\n", data[i]);
    }

    // Solution 3: Works but code is long and hard to maintain.
    {
        char data[]="ABBCCDDEEFFG";
        for (int i = 0; i < strlen(data); i++) {
            // Leading spaces
            for (int s = 3; s > i; s--) {
                printf(" ");
            }

            if (i==0) { // diamond start point
                printf("%c\n", data[0]);
            }
            else if(i%2 != 0 && i < 6) { // diamond opening
                printf("%c", data[i]);
                for (int s = 0; s < i; s++) {
                    printf(" ");
                }
                printf("%c\n", data[i]);
            }
            else if(i%2 != 0 && i > 6 && i < 11) { // diamond closing
                if (i==7) {
                    for (int k = 6; k < i; k++) {
                        printf(" ");
                    }
                    printf("%c", data[i]);
                    for (int l = 10; l > i; l--) {
                        printf(" ");
                    }
                    printf("%c\n", data[i+1]);
                }
                else if(i==9) {
                    for (int k = 7; k < i; k++) {
                        printf(" ");
                    }
                    printf("%c", data[i]);
                    for (int l = 10; l>i; l--) {
                        printf(" ");
                    }
                    printf("%c\n", data[i+1]);
                }
            }
            else if(i==11) { // diamond end point
                for (int m = 0; m < 3; m++){
                    printf(" ");
                }
                printf("%c\n", data[i]);
            }
        }
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
