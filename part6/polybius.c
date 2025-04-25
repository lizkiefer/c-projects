/*
*polybius.c / Random Number Generation and Encryption / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Sep 28, 2024
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char resultText[1024];

// Gets the position of a character in the character table
// Arguments: The character to search for, the table to search in
// Returns: An int of the index in the length-36 table, 0-35
// Returns -1 if character is not found
int getSquarePosition(char inChar, char *table)
{
    // Table is indices 0-35
    int tableIndex = -1;
    for (int i = 0; i < 36; i++)
    {
        if (table[i] == inChar) {
            tableIndex = i;
        }
    }
    return tableIndex;
}

// Gets the character for a provided row and column in the table,
// with rows and columns starting from 1
// Arguments: The row in the table, the column in the table, the table to search in
// Returns: The char for that position in the table
char getSquareChar(int rowIndex, int colIndex, char *table)
{
    return table[((rowIndex - 1) * 6) + (colIndex - 1)];
}

// Encodes a provided string into a series of integers using a polybius cipher
// Arguments: All program arguments, the number of arguments, the table to search in
// Returns: A string saved to a static resultText variable
const char *pbEncode(char inString[], int inStringLength, char *table)
{
    int resultIndex = 0;
    
    for (int i = 0; i < inStringLength; i++) {
        char currentChar = inString[i];
        // Convert to uppercase
        if (currentChar >= 97 && currentChar < 123)
        {
            currentChar -= 32;
        }
        
        int tableIndex = getSquarePosition(currentChar, table);
        
        if (tableIndex >= 0)
        {
            int rowIndex = tableIndex / 6 + 1;
            int colIndex = tableIndex % 6 + 1;
            // Add 48 to convert int to ASCII
            resultText[resultIndex] = rowIndex + 48;
            resultText[resultIndex + 1] = colIndex + 48;
            resultIndex += 2;
        }
    }
    return resultText;
}

// Decodes a provided cipher text string into a characters using a polybius cipher
// Arguments: All program arguments, the number of arguments, the table to search in
// Returns: A string saved to a static resultText variable
const char *pbDecode(char inString[], int inStringLength, char *table)
{
    int resultIndex = 0;
    
    // Combine all arg words into a single string with no spaces
    for (int i = 0; i < inStringLength; i += 2) {
        char currentChar = inString[i];
        // Convert to uppercase
        char resultChar = getSquareChar(inString[i] - 48, inString[i + 1] - 48, table);
        resultText[resultIndex] = resultChar;
        resultIndex += 1;
    }
    return resultText;
}
