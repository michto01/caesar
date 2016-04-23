/*! @file caesar.c
 *
 * Simple command line utility to encrypt/decrypt given string using caesar cipher.
 *
 * @date 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

typedef enum {
        CAESAR_UNKNOWN,
        CAESAR_SUCCESS,
        CAESAR_FAILURE
} status_t;

status_t calculate_key(char* key, int *shift);
status_t transform_string(char* str, int key);

int main(int argc, char **argv)
{
        char  key[3];
        char  plaintext[1000];

        fprintf(stdout, "Enter the string: ");
        scanf("%999[^\n]s", plaintext);

        fprintf(stdout, "Enter key [2 letters]:");
        getchar();
        scanf( "%2s", key);

        size_t len = strlen(plaintext);

        if (len ==  0) {
                fprintf(stderr, "Input string is empty, exiting.\n");
                return EXIT_FAILURE;
        }

        int k;
        if ( calculate_key( key, &k ) != CAESAR_SUCCESS ) {
                fprintf(stderr, "Error while processing the key.\n");
                return EXIT_FAILURE;
        } else {
                fprintf(stdout, "Key shift: %d\n", k);
                transform_string(plaintext, k);
        }

        fprintf(stdout, "The result is: %s\n", plaintext);
        return EXIT_SUCCESS;
}

status_t transform_string(char* str, int key)
{
        for (char* it = str; *it; ++it) {
                if (isalpha(*it)) {
                        int x = (((tolower(*it) - 'a') + key) % 26);
                        if (x > -1)
                                *it = x + 'a';
                        else
                                *it = (x + 'z' + 1);

                }
        }
        return CAESAR_SUCCESS;
}

status_t calculate_key(char* key, int *shift)
{
        if ( strlen(key) != 2 ) {
                *shift = -1;
                return CAESAR_FAILURE;
        }

        if ( !isalpha(tolower(key[0])) || !isalpha(tolower(key[1])) ) {
                *shift = -2;
                return CAESAR_FAILURE;
        }

        *shift = tolower(key[1]) - tolower(key[0]);
        return CAESAR_SUCCESS;
}

