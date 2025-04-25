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
    int identifier;
    char* name;
    long runTime;
    int priority;
} process_t;

typedef struct
{
    void* item;
    void* next;
    void* previous;
} queue_t;

// Creates a new queue item and adds it to the queue
// Arguments: The last queue in the list, the element use as the queue's item
// Returns: The queue_t struct
queue_t* push_queue(queue_t* queue, void* element)
{
    queue_t *newQueue;
    // Reserve as much space as needed for length of the array
    newQueue = malloc(sizeof(queue));
    newQueue->item = element;
    queue->next = newQueue;
    newQueue->previous = queue;
    newQueue->next = NULL;
    return newQueue;
}

// Removes the queue entry and returns its item, setting previous and next for other queue_t as needed
// Arguments: The queue entry to remove
// Returns: The item held by the queue_t
void* pop_queue(queue_t* queue)
{
    queue_t* previousQueue = queue->previous;
    previousQueue->next = NULL;
    
    if (queue->next != NULL)
    {
        queue_t* nextQueue = queue->next;
        nextQueue->previous = previousQueue;
        previousQueue->next = nextQueue;
    }
    else
    {
        previousQueue->next = NULL;
    }
    return queue->item;
}

// Removes the queue with the highest process priority and returns its process
// Arguments: The first entry in the queue to search
// Returns: The highest-priority process in the queue
process_t* remove_process(queue_t* queue)
{
    queue_t* highestPriorityQueue = queue;
    int highestPriority = 0;
    while (queue->next != NULL)
    {
        queue = queue->next;
        process_t* tempProcess = (process_t*)queue->item;
        if (tempProcess->priority > highestPriority)
        {
            highestPriorityQueue = queue;
            highestPriority = tempProcess->priority;
        }
    }
    
    return pop_queue(highestPriorityQueue);
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
        process_t *currentItem = queue->item;
        printf("Process %i: %s, runtime: %li, priority: %i\n", 
            currentItem->identifier,
            currentItem->name,
            currentItem->runTime,
            currentItem->priority);
    }
    printf("\n");
}
