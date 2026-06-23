/*
We take an array of integers, and remove the duplicates in the array.
We shift the unique values to the left and return the number of unique elements.
For example, if array is 
{1, 5, 3, 4, 5, 6, 6, 6, 9, 1} it should become 
{1, 5, 3, 4, 6, 9, x, x, x, x} and function should return 6. x is undefined.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nodup(int *arr, int len) {
    int num_dups = 0;
    for (int i = 0; i < len-num_dups; i++) {
        // Search to the left previous unique values
        for (int j = 0; j < i; j++) {
            if (arr[j] == arr[i]) {
                num_dups++;

                // Shift values from the right 
                for(int k = i; k < 8; k++) {
                    arr[k] = arr[k+1];
                    i--; // arr[i] contains a new value from the right: process this position again
                }
            }     
        }
    }
    return len - num_dups;
}

int main() {
    int arr[] = {1, 5, 3, 4, 5, 6, 6, 6, 9, 1};
    int len = sizeof(arr)/sizeof(int);
    int num_uniq = nodup(arr, len);
    printf("Length of array without duplicates is %d\n", num_uniq);
    for (int i = 0; i < num_uniq; i++) printf("%d ", arr[i]);
}
