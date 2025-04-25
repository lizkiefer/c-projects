/*
*cipher.c / Random Number Generation and Encryption / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Sep 28, 2024
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "polybius.h"

// Prints hints for program usage
void printUsage()
{
    printf("Not enough arguments received! Allowed flags are one of:\n");
    printf("-d <string>: Plaintext string to encode\n");
    printf("-e <string>: Cipher string to decode\n");
}

int main(int argc, char* argv[])
{
    // Holds 26 letters and ten numbers, no spaces or special characters
    char table[6][6] = { 
        {'A', 'B', 'C', 'D', 'E', 'F'}, 
        {'G', 'H', 'I', 'J', 'K', 'L'}, 
        {'M', 'N', 'O', 'P', 'Q', 'R'}, 
        {'S', 'T', 'U', 'V', 'W', 'X'}, 
        {'Y', 'Z', '0', '1', '2', '3'}, 
        {'4', '5', '6', '7', '8', '9'}
    };
    
    if (argc < 3) {
        printUsage();
        return -1;
    }
    
    for (int i = 2; i < argc; i++) {
        int newStringLength = strlen(argv[i]);
        char* newString = malloc(newStringLength);
        for (int j = 0; j < newStringLength; j++) {
            char currentChar = argv[i][j];
            newString[j] = argv[i][j];
        }
            
        if (strcmp(argv[1], "-d") == 0)
        {
            const char *output = pbDecode(newString, newStringLength, *table);
            printf("%s\n", output);
        }
        else if (strcmp(argv[1], "-e") == 0)
        {
            const char *output = pbEncode(newString, newStringLength, *table);
            printf("%s\n", output);
        }
        else
        {
            printUsage();
            return -1;
        }
    }
    
    return 0;
}
