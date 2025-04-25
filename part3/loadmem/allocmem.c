#include <stdio.h>
#include <stdlib.h>

// Static segment allocation, will remain allocated for full duration of program.
// Freed only on program exit.
static char staticStorage[1000*1000 * 5];

int main(int argc, char* argv[])
{
    printf("Static: %li\n", sizeof(staticStorage)); // Prints full size of block, 500,000 bytes
    
    // Heap allocation, memory is not reserved at execution time. Will contain garbage until memory is written
    char* heapStorage = malloc(1000*1000 * 10); // Will be NULL if allocation fails
    printf("Heap: %li\n", sizeof(heapStorage)); // Only prints 8 because that's the size of the first byte in the block
    // Will not be returned until free is called later or the program exits. Will not go out of scope.
    
    // Stack allocation, memory is allocated when the number of bytes is specified for the pointer
    char stackStorage[1000*1000 * 1]; // Reserves 100,000 bytes, immediately allocated because we specified the size now
    printf("Stack: %li\n", sizeof(stackStorage)); // Prints full size of block, 100,000 bytes
    // Will not be freed until the variable goes out of scope or the program exits
    
    free(heapStorage);
    return 0;
}
