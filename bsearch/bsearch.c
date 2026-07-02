/*
Take a list of English words at
https://raw.githubusercontent.com/dwyl/english-words/refs/heads/master/words_alpha.txt
Give a word, write a function to determine if the word is a valid English word.
This program compares the runtime performance of linear search vs binary search.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 1

// TODO Determine these dynamically
const int FILE_SIZE = 4235000;
const int NUM_WORDS = 370105; 

char ** load_dict(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Unable to open data file.\n");
        fclose(fp);
        return NULL;
    }

    char *buffer = malloc(FILE_SIZE);
    if (!buffer) {
        printf("Error: Allocation failed for file buffer.\n");
        fclose(fp);
        return NULL;
    }

    int bytes_read = fread(buffer, 1, FILE_SIZE, fp);
    buffer[bytes_read] = '\0';
    fclose(fp);

    char **words = malloc(NUM_WORDS * sizeof(char *));
    if (!words) {
        printf("Error: Allocation failed for word pointers.\n");
        free(buffer);
        return NULL;
    }

    int curr = 0;
    words[curr++] = buffer;
    for (int i = 0; i < bytes_read; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            if (i + 1 < bytes_read && buffer[i + 1] != '\0') {
                words[curr++] = &buffer[i + 1];
            }
        }
    }

    #if DEBUG
    printf("Successfully loaded %d words!\n", NUM_WORDS);
    printf("First word: %s\n", words[0]);
    printf("Last word: %s\n", words[NUM_WORDS - 1]);
    #endif

    return words;
}

bool linear_search(char **words, char *word) {
    for (int i = 0; i < NUM_WORDS; i++) {
        if (strcmp(words[i], word)==0) {
            printf("Linear search: found word in %d iterations.\n", i+1);
            return true;
        }
    }
    return false;
}

bool binary_search(char **words, char *word) {
    int i = 0;
    int old_pivot = -1, pivot = NUM_WORDS >> 1;
    int step = pivot;
    while (pivot >= 0 && pivot < NUM_WORDS) {
        i++;
        int comp_res = strcmp(words[pivot], word);
        if (comp_res == 0) {
            printf("Binary search: found word in %d iterations.\n", i);
            return true;
        }
        step = step > 1 ? (step + 1) >> 1 : 1;
        if (step == 1) {
            // Searched two adjacent words and didn't find a match
            if ((comp_res < 0 && pivot + 1 == old_pivot) || 
                (comp_res > 0 && pivot - 1 == old_pivot)) {
                break; 
            }
        }
        old_pivot = pivot;
        if (comp_res < 0) pivot += step;
        else if (comp_res > 0) pivot -= step;
    }
    return false;
}

bool is_in_dict(char **words, char *word, bool (*search)(char **, char *)) {
    bool found = search(words, word);
    if (!found) printf("Did not find a match in the dictionary.\n");
    return found;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: expecting exactly 1 program argument.\n");
        return 1;
    }
    char *word = argv[1];

    // Already downloaded, sorted and saved to the local system
    char **words = load_dict("sorted_words_alpha.txt");
    if (!words) {
        return 2;
    }

    is_in_dict(words, word, linear_search);
    is_in_dict(words, word, binary_search);

    return 0;
}