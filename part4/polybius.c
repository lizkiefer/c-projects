#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *pbEncode(const char *plaintext, char * table)
{
    return plaintext;
}

const char *pbDecode(const char *ciphertext, char * table)
{
    return ciphertext;
}

void printUsage()
{
    printf("Not enough arguments received! Allowed flags are one of:\n");
    printf("-d <string>: Plaintext string to encode\n");
    printf("-e <string>: Cipher string to decode\n");
}

int main(int argc, char* argv[])
{
    int doEncode;
    
    if (argc < 3) {
        printUsage();
        return -1;
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        doEncode = 0;
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
        doEncode = 1;
    }
    else
    {
        printUsage();
        return -1;
    }
    
    int totalChars = 0;
    char inStr[100];
    
    if (doEncode == 0) 
    {
        pbEncode(argv, NULL);
    }
    else
    {
        pbDecode(argv, NULL);
    }
    
    return 0;
}
