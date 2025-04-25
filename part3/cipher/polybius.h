/*
*polybius.h / Random Number Generation and Encryption / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Sep 28, 2024
*
*/

#include "polybius.c"

int getSquarePosition(char inChar, char *table);

char getSquareChar(int rowIndex, int colIndex, char *table);

const char *pbEncode(char *argv[], int argc, char *table);

const char *pbDecode(char *argv[], int argc, char *table);