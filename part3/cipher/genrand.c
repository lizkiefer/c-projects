/*
*genrand.c / Random Number Generation and Encryption / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Sep 28, 2024
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int modulus = 65536;
int multiplier = 863;
int increment = 152;
int seed = 12345;

// Provides a random number
// Arguments: The upper bound and lower bound of the range for the generated number
// Returns: A random integer between the given bounds
int genRand(int lower, int upper)
{
    seed = (multiplier * seed + increment++) % modulus;
    return lower + (seed % (upper - lower + 1));
}

int main(int argc, char* argv[])
{
    char* append = "w";
    char* fileName = "";
    // Set numCount to 0 to start, assume it'll get filled as an argument
    long numCount = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            append = "a";
        }
        else if (numCount == 0)
        {
            numCount = strtol(argv[i], NULL, 10);
        }
        else
        {
            fileName = argv[i];
        }
    }

    if (numCount <= 0 || fileName == "")
    {
        printf("Usage: ./genrand <number of numbers to generate> <output file name>\n");
        printf("Number of numbers to generate must be greater than zero\n");
        printf("-a: Optional flag, append to output file instead of overwriting\n");
        return 1;
    }
    
    FILE *file = fopen(fileName, append);
    for (int i = 0; i < numCount ; ++i)
    {
        fprintf(file, "%i\n", genRand(1, 100));
    }
    
    fclose(file);
    
    return 0;
}
