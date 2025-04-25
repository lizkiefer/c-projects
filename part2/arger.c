#include <stdio.h>
#include <string.h>

int countString(char* input)
{
    int length = 0;
    while (input[length] != '\0')
    {
        length++;
    }
    return length;
}

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-u") == 0)
        {
            int length = countString(argv[i + 1]);
            
            printf("%i\n", length);
            // printf("U%s\n", strlen(argv[i + 1]));
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            printf("L%s\n", argv[i + 1]);
        }
        else if (strcmp(argv[i], "-cap") == 0)
        {
            printf("CAP%s\n", argv[i + 1]);
        }
        
    }

    return 0;
}
