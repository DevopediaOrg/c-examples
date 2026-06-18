/*
Prints the Pascal's Triangle.
See https://en.wikipedia.org/wiki/Pascal%27s_triangle
*/

#include <stdio.h>
#include <string.h>

#define NUM 15

int main() {
    int prev[NUM] = {};
    int curr[NUM] = {};    

    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j <= i; j++) {
            curr[j] = (j == 0 || j == i) ? 
                       1 : prev[j-1] + prev[j];
            printf("%4d ", curr[j]);
        }
        printf("\n");
        memcpy(prev, curr, sizeof(curr));
    }
}


