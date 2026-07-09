/*
Checks if a given word is a palindrome.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(char *word) {
    int len = strlen(word);
    for (int i = 0;  i < len/2; i++) {
        if (word[i] != word[len-i-1]) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: expecting input word. Quitting...\n");
        return 1;
    }

    if (is_palindrome(argv[1])) printf("Word is a palindrome!\n");
    else printf("Word is a NOT palindrome!\n");
}
