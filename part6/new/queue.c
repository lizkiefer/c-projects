/*
*queue.c / Program Execution and Process Queue / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Oct 1, 2024
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void* item;
    void* next;
    void* previous;
} queue_t;

// Creates a new queue item and adds it to the queue
// Arguments: The last queue in the list, the element use as the queue's item
// Returns: The queue_t struct
queue_t* push_queue(queue_t* queue, char* element)
{
    // Reserve as much space as needed for length of the array
    queue_t *newQueue;
    newQueue = malloc(sizeof(queue));
    newQueue->item = malloc(strlen(element));
    strcpy(newQueue->item, element);
    queue->next = newQueue;
    newQueue->previous = queue;
    newQueue->next = NULL;
    return newQueue;
}

// Gets the number of queue entries
// Arguments: The first entry in the queue to search
// Returns: The length of the queue
int get_queue_size(queue_t* queue)
{
    int queueSize = 0;
    while (queue->next != NULL)
    {
        queue = queue->next;
        queueSize++;
    }
    
    return queueSize;
}

// Prints all process items in a queue
// Arguments: The first entry in the queue to search
// Returns: None
void print_queue(queue_t* queue)
{
    while (queue->next != NULL)
    {
        queue = queue->next;
        char* currentItem = queue->item;
        printf("%s", currentItem);
    }
    printf("\n");
}
