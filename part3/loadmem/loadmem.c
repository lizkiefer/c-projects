/*
*loadmem.c / Memory Layout and Memory Management / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Sep 28, 2024
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int n; // At least one fixed-size named item is required
    int intArray[];
} dyn_block;

// Allocates a new struct dyn_block with the given size
// Arguments: Length of the array held by the new block
// Returns: A new dyn_block struct
dyn_block *alloc_dyn_block(int blockSize)
{
    dyn_block *returnBlock;
    // Reserve as much space as needed for length of the array
    returnBlock = malloc(sizeof(int[blockSize]) + sizeof(int));
    return returnBlock;
}

// Stores a given int array into a dyn_block's array
// Arguments: The block to use, the array of integers to store, and the length of that array of ints
// Returns: The dyn_block struct
struct dyn_block* store_mem_blk(dyn_block* inBlock, int inInts[], int intCount)
{
    inBlock->n = intCount;
    for (int i = 0; i < intCount; ++i)
    {
        inBlock->intArray[i] = inInts[i];
    }
}

int main(int argc, char* argv[])
{
    // Allocate a new dynamic block
    int intCount = 10;
    dyn_block *newBlock = alloc_dyn_block(intCount);
    
    int saveInts[intCount];
    for (int i = 0; i < intCount; ++i)
    {
        saveInts[i] = i;
    }
    
    // Store the int array in the dynamic block
    store_mem_blk(newBlock, saveInts, intCount);
    printf("newBlock array contents: ");
    for (int i = 0; i < intCount; ++i)
    {
        printf("%i ", newBlock->intArray[i]);
    }
    printf("\n");
    
    // Free the dynamic block
    free(newBlock);
    
    // Read data file and store integers into dynamic block
    printf("Reading, storing, and reprinting contents of data file\n");
    FILE *intFile = fopen("./blocks.data", "r");
    char line[256];
    // First count how many lines there are so we know how many blocks to set up
    int blockCount = 0;
    while (fgets(line, sizeof(line), intFile))
    {
        blockCount++;
    }
    
    // Rewind to start of file to start working line by line
    rewind(intFile);
    dyn_block *blockArray[blockCount];
    int blockIndex = 0;
    while (fgets(line, sizeof(line), intFile)) 
    {
        // Count how many numbers the line contains so the block can be created
        int lineNumberCount = -1; // Using non-numeric characters to count lines
        // Start at -1 to account for newline and null character
        for (int i = 0; i < strlen(line); i++)
        {
            if ((int)line[i] < 48 || (int)line[i] >= 58) // Separator character like newline or space
            {
                lineNumberCount += 1;
            }
        }
        blockArray[blockIndex] = alloc_dyn_block(lineNumberCount);
        
        int maxNumLength = 2;
        int blockArrayIndex = 0;
        int currentNumber;
        int currentNumbersArray[lineNumberCount];
        for (int i = 0; i < strlen(line); i++)
        {
            if ((int)line[i] >= 48 && (int)line[i] < 58)
            {
                // Handle the entire number "word" at once, one or two characters
                if ((int)line[i + 1] >= 48 && (int)line[i + 1] < 58)
                {
                    // The next char is also a number, so combine them
                    char currentChars[3] = { line[i], line[i + 1], '\0' };
                    currentNumber = atoi(currentChars);
                    i++; // Skip the next character, we already got it
                }
                else
                {
                    // Single digit number, add it directly
                    currentNumber = line[i] - '0';
                }
            }
            else if ((int)line[i] == 32 || (int)line[i] == 10) // Separator character like space and newline
            {
                // Place the number into the array and get ready for the next number
                currentNumbersArray[blockArrayIndex] = currentNumber;
                // currentNumber = "";
                blockArrayIndex++;
            }
        }
        // Store the number array into the current block
        store_mem_blk(blockArray[blockIndex], currentNumbersArray, lineNumberCount);
        // Advance to the next block
        blockIndex++;
    }
    
    // Print block contents
    for (int i = 0; i < blockCount; i++)
    {
        for (int j = 0; j < blockArray[i]->n; j++)
        {
            printf("%i ", blockArray[i]->intArray[j]);
        }
        printf("\n");
        
        free(blockArray[i]);
        printf("Block %i freed\n", i);
    }
    
    fclose(intFile);
    return 0;
}
