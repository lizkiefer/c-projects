#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int modulus = 65536;
int multiplier = 863;
int increment = 152;
int seed = 74;

int genRand(int lower, int upper)
{
    seed = (((seed * multiplier) + increment++) % modulus);
    return (seed % upper + 1) + lower - 1; // Bounds do not work correctly
}

int main(int argc, char* argv[])
{
    char* append = "w";
    char* fileName;
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

    if (numCount <= 0)
    {
        printf("Usage: ./genrand <number of numbers to generate> <output file name>\n");
        printf("Number of numbers to generate must be greater than zero\n");
        printf("-a: Optional flag, append to output file instead of overwriting\n");
        return 1;
    }
    
    FILE *file = fopen("./outputFile.txt", append);
    for (int i = 0; i < 5 ; ++i)
    {
        fprintf(file, "%i\n", genRand(5, 20));
    }
    
    fclose(file);
    
    return 0;
}
