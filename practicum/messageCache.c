/*
*practicum.c / Practicum I / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Nov 6, 2024
*
*/

#define MESSAGE_CACHE_SIZE 16

// Message cache
// A simple array with 16 slots available
// Cache can be searched with a simple loop, checking identifier for match
// Other methods considered:
// Linked list. Would be expandable by adding more items to the list,
// But here we want the cache to always be the same size
// And we don't want to deal with reordering the list
static message message_cache[MESSAGE_CACHE_SIZE];
static int message_cache_counters[MESSAGE_CACHE_SIZE];
static int message_cache_counter = 0;
static int message_cache_hit_counter = 0;

// Stores the input message to the cache
// Uses either LRU or Random Replacement, depending on flag
// Arguments: The message object to store and an lru flag to indicate cache methods
// lru = 0 -> Use Least-Recently Used
// lru = 1 -> Use Random Replacement
// Returns: The index of the cache where the message was stored
int store_msg_cache(message* inMessage, int lru)
{
    // Save message to cache, finding the first unused spot
    size_t index = 0;
    for (index = 0; index < MESSAGE_CACHE_SIZE; index++)
    {
        // Identifier is zero for undefined messages
        if (message_cache[index].identifier == 0)
        {
            message_cache[index] = *inMessage;
            break;
        }
    }
    
    // No empty slot was found in the cache
    if (index >= MESSAGE_CACHE_SIZE)
    {
        int storeIndex = 0;
        if (lru == 0) {
            storeIndex = genLru(MESSAGE_CACHE_SIZE, message_cache_counters);
            
            // Update the least-recently used array
            message_cache_counters[storeIndex] = message_cache_counter;
            message_cache_counter++;
        }
        else
        {
            // Generate a random position to overwrite
            storeIndex = genRand(0, 15, seed);
        }
        // printf("Storing %i in cache at %i\n", inMessage->identifier, storeIndex);
        message_cache[storeIndex] = *inMessage;
    }
    
    return index;
}

// Retrieves the message with the given identifier
// Will first attempt to find the message in the cache
// If not found, load the message from disk
// After loading the message from disk, store it in the cache
// The lru flag determines the caching method when storing in the cache
// Arguments: The identifier of the message and an lru flag to indicate cache methods
// Returns: The retrieved message object
message *retrieve_msg(int identifier, int lru)
{
    // First check the cache for the message
    // printf("Retrieving message %i\n", identifier);
    
    message *returnMessage = NULL;
    for (int i = 0; i < MESSAGE_CACHE_SIZE; i++)
    {
        if (message_cache[i].identifier == identifier)
        {
            // printf("Message %i found in cache position %i\n", identifier, i);
            message_cache_hit_counter++;
            returnMessage = &message_cache[i];
            
            // Set the counter to show this cache position was recently used
            message_cache_counters[i] = message_cache_counter;
            message_cache_counter++;
            break;
        }
    }
    
    if (returnMessage == NULL) // If message was not found in cache, load it from disk
    {
        // printf("Message %i not found in cache, reading from disk\n", identifier);
        // Create file name
        char fileName[20];
        snprintf(fileName, sizeof(fileName), "%i.txt", identifier);
        FILE *file = fopen(fileName, "r");
        
        // Load message members line by line
        char timeSent[20];
        fgets(timeSent, sizeof(timeSent), file);
        timeSent[strcspn(timeSent, "\n")] = '\0';
        
        char sender[20];
        fgets(sender, sizeof(sender), file);
        sender[strcspn(sender, "\n")] = '\0';
        
        char receiver[20];
        fgets(receiver, sizeof(receiver), file);
        receiver[strcspn(receiver, "\n")] = '\0';
        
        char content[1024];
        fgets(content, sizeof(content), file);
        content[strcspn(content, "\n")] = '\0';
        
        char deliveredString[sizeof(int)];
        fgets(deliveredString, sizeof(deliveredString), file);
        int delivered;
        delivered = atoi(deliveredString);
        
        fclose(file);
        
        // Create message object using loaded members
        returnMessage = create_msg(identifier, timeSent, sender, receiver, content, delivered);
        store_msg_cache(returnMessage, lru);
    }
    
    return returnMessage;
}

// Prints the message cache content for debugging
void printCache()
{
    printf("Current cache: ");
    for (int i = 0; i < MESSAGE_CACHE_SIZE; i++)
    {
        printf("%i ", message_cache[i].identifier);
    }
    printf("\n");
}
