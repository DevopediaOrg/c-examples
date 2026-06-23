/*
Take a string and reverse the string in-place. That is, the reversed string must be stored
in the location of the original string.
For example, if string is "ABCD EFG" it should become "GFE DCBA".
*/

#include <stdio.h>
#include <string.h>

void reverse(char *data) {
    int len = strlen(data);

    // Works for both odd and even len
    for (int i = 0; i < len/2; i++) {
        char temp = data[i];
        data[i] = data[len - i - 1];
        data[len - i - 1] = temp;
    }
}

int main() {
    char data[] = "HelloWorld";

    printf("Original: %s\n", data);
    reverse(data);
    printf("Reversed: %s\n", data);

    return 0;
}