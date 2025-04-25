/*
*genchars.c / Multiprocessing in C / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Oct 3, 2024
*
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "./queue.c"

int modulus = 65536;
int multiplier = 863;
int increment = 152;
int seed = 123456;

int stringCount = 10000;
int stringsPerProcess = 100;
int lengthPerString = 64;

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
    // Write strings to file
    printf("Generating %i strings and writing to ./outputfile.txt\n", stringCount);
    FILE *file = fopen("./outputfile.txt", "w");
    for (int i = 0; i < stringCount ; ++i)
    {
        for (int j = 0; j < lengthPerString ; ++j)
        {
            // Random lowercase letters
            fprintf(file, "%c", genRand(97, 122));
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    
    // Open the file and load the strings into a queue_t
    printf("Loading strings from ./outputfile.txt\n");
    queue_t *head;
    head = malloc(sizeof(*head));
    queue_t *currentQueue = head;
    FILE *inFile = fopen("./outputfile.txt", "r");
    char line[lengthPerString + 2];
    int lineCount = 0;
    while (fgets(line, sizeof(line), inFile))
    {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        push_queue(currentQueue, line);
        currentQueue = currentQueue->next;
        // printf("Inserted new queue %i, contents %s", lineCount, currentQueue->item);
        lineCount++;
    }
    
    if (lineCount == 0)
    {
        printf("Error, input file was empty!\n");
        return -1;
    }
    
    // printf("Printing queue\n");
    // print_queue(head);
    
    // Go through queue stringsPerProcess at a time and start subprocesses
    pid_t processId = getpid(); // Used for unique output file name
    int totalStringCount = 1;
    int processStringCount = 0;
    char outputFile[100];
    // Include PID in output file name
    snprintf(outputFile, sizeof(outputFile), "./cipherOutput-%i.txt", processId);
    printf("Starting subprocesses and appending output to %s\n", outputFile);
    
    queue_t* queue = head;

    char* argumentList[stringsPerProcess + 3]; // 3 extra for process name, -e, and NULL
    argumentList[0] = "./cipher";
    argumentList[1] = "-e";
    if (access("./cipher", F_OK) != 0) {
        printf("Error, ./cipher does not exist!\n");
        return -1;
    }
    
    while (queue->next != NULL)
    {
        queue = queue->next;
        
        // Set up a new process every stringsPerProcess
        if (totalStringCount % stringsPerProcess == 0) 
        {
            argumentList[stringsPerProcess + 2] = NULL;
            // for (int i = 0; i < stringsPerProcess + 3; i++)
            // {
                // printf("%s ", argumentList[i]);
            // }
            // printf("\n");
                
            // Create subprocess
            pid_t pid = fork();
            if (pid != 0)
            {
                int outFile = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
                dup2(outFile, 1);
                close(outFile);
                execvp("./cipher", argumentList);
            }
        
            // Reset the argument list for the next process
            memset(argumentList, 0, sizeof(argumentList));
            argumentList[0] = "./cipher";
            argumentList[1] = "-e";
            processStringCount = 0;
        }
        char* currentItem = queue->item;
        argumentList[processStringCount + 2] = currentItem;
        totalStringCount++;
        processStringCount++;
    }
    
    return 0;
}
