#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========================================
// Correct char * return example
// ===========================================
char *allocate_str_ok1(size_t n, char init)
{
    char *p = malloc(n + 1); // n+1 bytes
    memset(p, init, n);
    p[n] = 0;
    return p;
}

// ===========================================
// Wrong char *p argument example
// ===========================================
void allocate_str_ko(char *p, size_t n, char init)
{
    p = malloc(n + 1);
    memset(p, init, n);
    p[n] = 0;
}

// ===========================================
// Correct char **p argument example
// ===========================================
void allocate_str_ok2(char **p, size_t n, char init)
{
    *p = malloc(n + 1);
    memset(*p, init, n);
    (*p)[n] = 0;
}

void main()
{
    char *ptr = NULL;
    ptr = allocate_str_ok1(10, 'A');
    printf("ok1: %s\n", ptr);
    free(ptr); ptr = NULL;

    allocate_str_ko(ptr, 10, 'A');
    printf(" ko: %s\n", ptr);
    free(ptr); ptr = NULL;

    allocate_str_ok2(&ptr, 10, 'A');
    printf("ok2: %s\n", ptr);
    free(ptr); ptr = NULL;
}
