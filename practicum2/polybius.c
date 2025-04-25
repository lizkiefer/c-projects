/*
 * polybius.c / Practicum 2 / Program in C
 *
 * Liz Kiefer / CS5600 / Northeastern University
 * Fall 2024 / Dec 1, 2024
 *
 */

// Gets the position of a character in the character table
// Arguments: The character to search for, the table to search in
// Returns: An int of the index in the length-100 table, 0-99
// Returns -1 if character is not found
int getSquarePosition(char inChar, char *table)
{
    // Table is indices 0-99
    int tableIndex = -1;
    for (int i = 0; i < 100; i++)
    {
        // printf("index: %c\n", table[i]);
        if (table[i] == inChar) {
            tableIndex = i;
            break;
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
    return table[(rowIndex * 10) + colIndex];
}

// Encodes a provided string into a series of integers using a polybius cipher
// Arguments: All program arguments, the number of arguments, the table to search in
// Returns: A string with the encrypted value
const char *pbEncode(char inString[], char encryptionLine[], char *table)
{
    memset(encryptionLine, 0, 1024);

    int resultIndex = 0;
    for (int i = 0; i < strlen(inString); i++) {
        char currentChar = inString[i];
        int tableIndex = getSquarePosition(currentChar, table);
        
        if (tableIndex >= 0)
        {
            int rowIndex = tableIndex / 10;
            int colIndex = tableIndex % 10;
            // Add 48 to convert int to ASCII
            encryptionLine[resultIndex] = rowIndex + 48;
            encryptionLine[resultIndex + 1] = colIndex + 48;
            resultIndex += 2;
        }
    }
    return encryptionLine;
}

// Decodes a provided cipher text string into a characters using a polybius cipher
// Arguments: All program arguments, the number of arguments, the table to search in
// Returns: A string with the decrypted value
const char *pbDecode(char inString[], char encryptionLine[], char *table)
{
    memset(encryptionLine, 0, sizeof(*encryptionLine));
    int resultIndex = 0;
    
    // Combine all arg words into a single string with no spaces
    for (int i = 0; i < strlen(inString); i += 2) {
        char currentChar = inString[i];
        char resultChar = getSquareChar(inString[i] - 48, inString[i + 1] - 48, table);
        encryptionLine[resultIndex] = resultChar;
        resultIndex += 1;
    }
    return encryptionLine;
}
