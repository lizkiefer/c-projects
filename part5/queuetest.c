/*
*queue.c / Program Execution and Process Queue / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Sep 30, 2024
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./queue.c"

int main(int argc, char* argv[])
{
    queue_t *head;
    head = malloc(sizeof(*head));
    process_t *newItem;
    queue_t *currentQueue = head;
    printf("Inserting 10 queue items\n");
    for (int i = 0; i < 10; i++)
    {
        newItem = malloc(sizeof(*newItem));
        newItem->identifier = i;
        newItem->name = "TEST";
        newItem->runTime = 60.0;
        newItem->priority = 24 % (i + 3);
        push_queue(currentQueue, newItem);
        currentQueue = currentQueue->next;
        printf("Inserted new queue %i\n", i);
    }
    
    printf("Looping through 10 queue items and printing data\n");
    print_queue(head);
    
    printf("Popping last process off queue and printing its name and identifier\n");
    process_t *fetchedProcess = pop_queue(currentQueue);
    printf("%s: %i\n", fetchedProcess->name, fetchedProcess->identifier);
    printf("\n");
    
    int queueSize = get_queue_size(head);
    printf("Looping through remaining %i queue items and printing data\n", queueSize);
    print_queue(head);
    
    printf("Removing process with highest priority and printing its name and identifier\n");
    process_t *highestProcess = remove_process(head);
    printf("Process %i: %s, runtime: %li, priority: %i\n", 
        highestProcess->identifier,
        highestProcess->name,
        highestProcess->runTime,
        highestProcess->priority);
    printf("\n");
    
    queueSize = get_queue_size(head);
    printf("Looping through remaining %i queue items and printing data\n", queueSize);
    print_queue(head);
    
    return 0;
}
