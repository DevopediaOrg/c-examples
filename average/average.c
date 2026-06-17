#include <stdio.h>
#include <math.h>

double average(unsigned int arr[], unsigned int n) { // unsigned int *arr
    double sum = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i]; // *(arr+i)
    }

    return sum / n;
}

int main() {
    unsigned int scores[] = { 67, 55, 89, 77, 60, 72, 84, 63, 91, 59 };
    double mean = average(scores, sizeof(scores) / sizeof(unsigned int));
    printf("%.3g", mean);
}
