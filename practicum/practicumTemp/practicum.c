/*
*practicum.c / Practicum I / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Nov 6, 2024
*
*/

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "genRand.h"
#include "message.h"
#include "messageCache.h"

int main(int argc, char* argv[])
{
    // Set seed to current thread for some randomness
    seed = (unsigned long)pthread_self();
    
    int totalMessages = 50;
    
    // Create all messages
    for (int i = 0; i < totalMessages; i++)
    {
        // Identifier is always an increasing number here for easy access later
        // It could be non-sequential, but we're accessing messages using simple loops
        int identifier = 1234 + i;
        char timeSent[] = "the time sent";
        char sender[] = "the sender";
        char receiver[] = "the receiver";
        char content[] = "test content";
        bool delivered = 1;
        message *newMessage = create_msg(identifier, timeSent, sender, receiver, content, delivered);
        
        // Store the message to the disk
        store_msg(newMessage);
        // Store the message to the cache, defaulting to LRU, it doesn't matter yet
        store_msg_cache(newMessage, 0);
    }
    
    // Attempt to read 1000 random messages with Least-Recently Used
    int totalAccesses = 1000;
    int lru = 0; // 0 = use LRU
    message_cache_hit_counter = 0;
    for (int i = 0; i < totalAccesses; i++)
    {
        int messageIndex = genRand(0, totalMessages - 1, seed);
        message *retrievedMessage = retrieve_msg(1234 + messageIndex, lru);
        // printf("ID: %i, content: %s, delivered: %i\n", retrievedMessage->identifier, retrievedMessage->content, retrievedMessage->delivered);
    }
    printf("Total hits with LRU: %i\n", message_cache_hit_counter);
    printf("Total misses with LRU: %i\n", totalAccesses - message_cache_hit_counter);
    printf("Cache hit ratio with LRU: %f\n", message_cache_hit_counter / (float)totalAccesses);
    
    // Attempt to read 1000 random messages with Random Replacement
    lru = 1; // 1 = use RR
    message_cache_hit_counter = 0;
    for (int i = 0; i < totalAccesses; i++)
    {
        int messageIndex = genRand(0, totalMessages - 1, seed);
        message *retrievedMessage = retrieve_msg(1234 + messageIndex, lru);
        // printf("ID: %i, content: %s, delivered: %i\n", retrievedMessage->identifier, retrievedMessage->content, retrievedMessage->delivered);
    }
    printf("Total hits with Random Replacement: %i\n", message_cache_hit_counter);
    printf("Total misses with Random Replacement: %i\n", totalAccesses - message_cache_hit_counter);
    printf("Cache hit ratio with Random Replacement: %f\n", message_cache_hit_counter / (float)totalAccesses);
    return 0;
}
