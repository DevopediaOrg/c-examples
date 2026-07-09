/*
This code implements an encoder and a decoder for Morse Code.

The International Morse Code can be seen at
https://en.wikipedia.org/wiki/Morse_code

While encoding, source symbols (letters or digits) of the same word
are separated by a single space. Source words are separated by
three spaces. If original message has punctuation, it is replaced
with a space. Multiple consecutive spaces are replaced with a single
space before encoding.

While decoding, all letters are output in uppercase.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char * digits[] = {
    // 0        1        2        3        4
    "-----", ".----", "..---", "...--", "....-",
    // 5        6        7        8        9
    ".....", "-....", "--...", "---..", "----."
};

char * letters[] = {
    // A      B       C       D      E
    ".-",   "-...", "-.-.", "-..",  ".",
    // F      G       H       I      J
    "..-.", "--.",  "....", "..",   ".---",
    // K      L       M       N      O
    "-.-",  ".-..", "--",   "-.",   "---",
    // P      Q       R       S      T
    ".--.", "--.-", ".-.",  "...",  "-",
    // U      V       W       X      Y
    "..-",  "...-", ".--",  "-..-", "-.--",
    // Z
    "--.."
};

char search(char * needle, char * haystack[], int size, char start) {
    for (int i = 0; i < size; i++) {
        if (strcmp(needle, haystack[i]) == 0) return start + i;
    }
    return '\0';
}

char * decoder(char const * enc_msg) {
    char * decoded_msg = calloc(strlen(enc_msg), sizeof(char));

    // Each character can be at most 5 dots or dashes plus NUL character
    char curr_symbol[5+1] = {};

    int num_spaces = 0;
    char curr_char;
    char dec_char;
    for (int i = 0; i < strlen(enc_msg); i++) {
        curr_char = enc_msg[i];
        if (curr_char == ' ') {
            num_spaces++;
            if (num_spaces == 3) { // three spaces => word boundary
                dec_char = ' ';
            }
            else if (strlen(curr_symbol) == 5) { // digit
                dec_char = search(curr_symbol, digits, sizeof(digits) / sizeof(char*), '0');
            }
            else { // letter
                dec_char = search(curr_symbol, letters, sizeof(letters) / sizeof(char*), 'A');
            }
            decoded_msg[strlen(decoded_msg)] = dec_char;
            memset(curr_symbol, 0, sizeof(curr_symbol)); // reset to receive next symbol
        }
        else {
            num_spaces = 0;
            curr_symbol[strlen(curr_symbol)] = curr_char;
        }
    }

    return decoded_msg;
}

char * encoder(char const * msg) {
    // Each character can be at most 5 dots or dashes plus a space
    char * encoded_msg = malloc(strlen(msg)*5 + 1);
    encoded_msg[0] = '\0';

    char curr_char, prev_char = '\0';
    for (int i = 0; i < strlen(msg); i++) {
        curr_char = msg[i];
        if (isalpha(curr_char)) {
            int idx = toupper(curr_char) - 'A';
            strcat(encoded_msg, letters[idx]);
            strcat(encoded_msg, " ");
        }
        else if (isdigit(curr_char)) {
            int idx = curr_char - '0';
            strcat(encoded_msg, digits[idx]);
            strcat(encoded_msg, " ");
        }
        else {
            curr_char = ' ';
            if (curr_char == ' ' && prev_char != ' ') {
                strcat(encoded_msg, "  ");
            }
        }
        prev_char = curr_char;
    }

    return encoded_msg;
}

int main() {
    char msg[]  = {
        "Lorem's Ipsum is simply, dummy text of the printing and typesetting industry."
    };

    char * enc_msg = encoder(msg);
    printf("Encoded message: %s\n", enc_msg);

    char * dec_msg = decoder(enc_msg);
    printf("Decoded message: %s\n", dec_msg);

    return 0;
}