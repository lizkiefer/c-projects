/*
 * polybius.h / Practicum 2 / Program in C
 *
 * Liz Kiefer / CS5600 / Northeastern University
 * Fall 2024 / Dec 1, 2024
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "polybius.c"

// Gets the position of a character in the character table
// Arguments: The character to search for, the table to search in
// Returns: An int of the index in the length-100 table, 0-99
// Returns -1 if character is not found
int getSquarePosition(char inChar, char *table);

// Gets the character for a provided row and column in the table,
// with rows and columns starting from 1
// Arguments: The row in the table, the column in the table, the table to search in
// Returns: The char for that position in the table
char getSquareChar(int rowIndex, int colIndex, char *table);

// Encodes a provided string into a series of integers using a polybius cipher
// Arguments: All program arguments, the number of arguments, the table to search in
// Returns: A string with the encrypted value
const char *pbEncode(char inString[], char encryptionLine[], char *table);

// Decodes a provided cipher text string into a characters using a polybius cipher
// Arguments: All program arguments, the number of arguments, the table to search in
// Returns: A string with the decrypted value
const char *pbDecode(char inString[], char encryptionLine[], char *table);