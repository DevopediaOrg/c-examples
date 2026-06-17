#include <stdio.h>

// Wrong: Shows arguments passed by value
void swap_ko(int x, int y)
{
    int old_y;
    old_y = y;
    y = x;
    x = old_y;
    printf("swap_ko(): %p %p : %d %d\n", &x, &y, x, y);
}

// Correct: Shows arguments passed by reference
void swap_ok(int *x, int *y)
{
    int old_y;
    old_y = *y;
    *y = *x;
    *x = old_y;
    printf("swap_ok(): %p %p : %d %d\n", x, y, *x, *y);
}

void main()
{
    int x = 5, y = 10;

    swap_ko(x, y);
    printf("main(): %p %p : %d %d\n", &x, &y, x, y);

    swap_ok(&x, &y);
    printf("main(): %p %p : %d %d\n", &x, &y, x, y);
}