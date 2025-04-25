/*
*practicum.c / Practicum I / Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Nov 6, 2024
*
*/

#include "message.c"

// Creates a new message object
// Arguments: A numeric identifier, the time the message was sent, the sender, the receiver, the message content, and a delivered status
// Returns: A new message object
message *create_msg(int identifier, char* timeSent, char* sender, char* receiver, char* content, int delivered);

// Stores the input message to the disk, writing each member to one line in its own file
// Arguments: A message object to store
// Returns: 0
int store_msg(message* inMessage);