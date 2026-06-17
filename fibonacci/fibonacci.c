#include <stdio.h>

// See https://en.wikipedia.org/wiki/Fibonacci_sequence
// Fibonacci: 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377

#define NUM 15

/* Generate Fibonacci sequence of N numbers.
   We keep track of numbers and print at the end.
*/
void method_0(int N) {
    int fib[N];
    fib[0] = 0;
    fib[1] = 1;
    for(int n = 2; n < N; n++) {
        fib[n] = fib[n-1] + fib[n-2];
    }
    for(int n = 0; n < N; n++) {
        printf("%d ", fib[n]);
    }
    printf("\n");
}

/* Generate Fibonacci sequence of N numbers.
   We print each number as it is generated.
*/
void method_1(int N) {
    int Fn_2 = 0;
    int Fn_1 = 1;

    printf("%d %d ", Fn_2, Fn_1);

    for(int n = 2; n < N; n++) {
        int Fn = Fn_1 + Fn_2; 
        printf("%d ", Fn);
        Fn_2 = Fn_1;
        Fn_1 = Fn;
    }
    printf("\n");
}


int main() {
    method_0(NUM);
    method_1(NUM);
    return 0;
}