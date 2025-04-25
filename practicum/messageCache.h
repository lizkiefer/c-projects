/*
*practicum.c / Practicum I / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Nov 6, 2024
*
*/

#include "messageCache.c"

// Prints the message cache content for debugging
void printCache();

// Stores the input message to the cache
// Uses either LRU or Random Replacement, depending on flag
// Arguments: The message object to store and an lru flag to indicate cache methods
// lru = 0 -> Use Least-Recently Used
// lru = 1 -> Use Random Replacement
// Returns: The index of the cache where the message was stored
int store_msg_cache(message* inMessage, int lru);

// Retrieves the message with the given identifier
// Will first attempt to find the message in the cache
// If not found, load the message from disk
// After loading the message from disk, store it in the cache
// The lru flag determines the caching method when storing in the cache
// Arguments: The identifier of the message and an lru flag to indicate cache methods
// Returns: The retrieved message object
message *retrieve_msg(int identifier, int lru);