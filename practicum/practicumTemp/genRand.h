/*
*practicum.c / Practicum I / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Nov 6, 2024
*
*/

#include "genRand.c"

// Provides a random number
// Arguments: The upper bound and lower bound of the range for the generated number
// Returns: A random integer between the given bounds
int genRand(int lower, int upper, int inSeed);

// Provides the least-recently used index in the cache by looping through the set of counters
// messageCacheCounters contains an array of ints. When a cache item is accessed, the int there is given a new higher value to indicate it was most recently used
// Arguments: The total size of the cache, and the array containing cache recently-used data
// Returns: The least-recently used index in the cache
int genLru(int messageCacheSize, int *messageCacheCounters);