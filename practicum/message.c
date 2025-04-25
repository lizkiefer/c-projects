/*
*practicum.c / Practicum I / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Nov 6, 2024
*
*/

#define MESSAGE_CACHE_SIZE 16

typedef struct
{
    int identifier;
    char timeSent[20];
    char sender[20];
    char receiver[20];
    char content[512];
    int delivered;
} message;

// Creates a new message object
// Arguments: A numeric identifier, the time the message was sent, the sender, the receiver, the message content, and a delivered status
// Returns: A new message object
message *create_msg(int identifier, char* timeSent, char* sender, char* receiver, char* content, int delivered)
{
    int message_size = sizeof(int) + sizeof(char[20]) + sizeof(char[20]) + sizeof(char[20]) + sizeof(char[512]) + sizeof(int);
    message *returnMessage;
    // Reserve as much space as needed for the size of the object
    returnMessage = malloc(message_size);
    returnMessage->identifier = identifier;
    strcpy(returnMessage->timeSent, timeSent);
    strcpy(returnMessage->sender, sender);
    strcpy(returnMessage->receiver, receiver);
    strcpy(returnMessage->content, content);
    strcpy(returnMessage->content, content);
    returnMessage->delivered = delivered;
    return returnMessage;
}

// Stores the input message to the disk, writing each member to one line in its own file
// Arguments: A message object to store
// Returns: 0
int store_msg(message* inMessage)
{
    // Create file name
    char fileName[20];
    snprintf(fileName, sizeof(fileName), "%i.txt", inMessage->identifier);
    
    // Save message to file
    FILE *file = fopen(fileName, "w");
    
    fprintf(file, "%s\n", inMessage->timeSent);
    fprintf(file, "%s\n", inMessage->sender);
    fprintf(file, "%s\n", inMessage->receiver);
    fprintf(file, "%s\n", inMessage->content);
    fprintf(file, "%i\n", inMessage->delivered);
    
    fclose(file);
    return 0;
}
