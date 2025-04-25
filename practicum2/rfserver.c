/*
 * rfserver.c -- TCP Socket Server / Practicum 2 / Program in C
 * 
 * Liz Kiefer / CS5600 / Northeastern University
 * Fall 2024 / Dec 1, 2024
 * adapted from: 
 *     https://www.educative.io/answers/how-to-implement-tcp-sockets-in-c
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "./polybius.h"

#define THREADCOUNT 10

typedef struct {
    int clientSock;
    int socketDesc;
    int inUse;
    char clientMessage[8192];
    char currentFile[1024];
    char encryptionLine[1024];
    pthread_mutex_t mut;
    pthread_cond_t cond;
} workerData;

static workerData clientData[THREADCOUNT];

// Returns a message to the socket and releases all resources for the thread
// Arguments: The index of the current worker, the message to send
// Returns: An int 0 to indicate success
int sendMessage(int workerIndex, char* message)
{
    if (send(clientData[workerIndex].clientSock, message, strlen(message), 0) < 0){
        printf("Can't send\n");
        close(clientData[workerIndex].socketDesc);
        close(clientData[workerIndex].clientSock);
        exit(-1);
    }
    // sleep(10); // Delay for testing threads
    printf("Releasing lock on file %s for thread %i\n", clientData[workerIndex].currentFile, workerIndex);
    clientData[workerIndex].inUse = 0;
    pthread_mutex_unlock (&clientData[workerIndex].mut);
    pthread_cond_signal (&clientData[workerIndex].cond);
    return 0;
}

// Performs work on files within a thread
// Arguments: The index of the current worker
void *worker(void *data)
{
    // Encryption table setup
    char table[10][10] = { 
        {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, 
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
        {'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'},
        {'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N'},
        {'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', '!', '@', '#', '$', '%', '^', '&', '*'},
        {'(', ')', '_', '+', '-', '=', ',', '.', '/', '<'},
        {'>', '?', ';', ':', '\'', '"', '|', '\\', '~', '`'},
        {'[', ']', '{', '}', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    char server_message[8196];
    int workerIndex = *(int*)data;
    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));

    printf("Incoming request\n");
    char *fileMode = strtok(clientData[workerIndex].clientMessage, "\n");
    printf("File Mode: %s\n", fileMode);
    char *fileName = strtok(NULL, "\n");
    printf("File Name: %s\n", fileName);
    
    // Check if any other thread is currently using the file
    for (int i = 0; i < THREADCOUNT; i++)
    {
        if (i != workerIndex && strcmp(clientData[i].currentFile, fileName) == 0 && clientData[i].inUse == 1)
        {
            // File is currently being used by another active thread
            printf("File %s currently in use by thread %i, waiting for release\n", clientData[i].currentFile, i);
            pthread_cond_wait(&clientData[i].cond, &clientData[i].mut);
        }
    }
    
    // Check if file exists
    strcpy(clientData[workerIndex].currentFile, fileName);
    pthread_mutex_lock(&clientData[workerIndex].mut);
    
    if (strcmp(fileMode, "w") == 0)
    {
        FILE *localFile = fopen(fileName, "w");
        if (localFile == NULL) {
            printf("Unable to open file %s\n", fileName);
            sendMessage(workerIndex, "Unable to open file\n");
        }
        else
        {
            char *line;
            line = strtok(NULL, "\n");
            while (line != NULL) {
                fprintf(localFile, "%s\n", pbEncode(line, clientData[workerIndex].encryptionLine, *table));
                line = strtok(NULL, "\n");
            }
            fclose(localFile);
            
            sendMessage(workerIndex, "Successfully wrote new file\n");
        }
    }
    else if (strcmp(fileMode, "r") == 0)
    {
        if (access(fileName, F_OK) != 0)
        {
            printf("Unable to open file %s\n", fileName);
            sendMessage(workerIndex, "Unable to open file\n");
        }
        else
        {
            // Read local file and add it to the server string
            FILE *localFile = fopen(fileName, "r");
            char line[1024] = "";
            strcat(server_message, "0\n"); // Success response
            while (fgets(line, sizeof(line), localFile))
            {
                strcat(server_message, pbDecode(line, clientData[workerIndex].encryptionLine, *table));
                strcat(server_message, "\n");
            }
            sendMessage(workerIndex, server_message);
        }
    }
    else if (strcmp(fileMode, "d") == 0)
    {
        if (access(fileName, F_OK) != 0)
        {
            printf("Unable to open file %s\n", fileName);
            sendMessage(workerIndex, "Unable to open file\n");
        }
        else
        {
            if (remove(fileName) == 0)
            {
                sendMessage(workerIndex, "File removed successfully.\n");
            }
            else
            {
                sendMessage(workerIndex, "Unable to remove file.\n");
            }
        }
    }
    else
    {
        sendMessage(workerIndex, "Invalid file operation. Options are: WRITE, GET, RM\n");
    }
}

int main(void)
{
    int socket_desc, client_sock;
    socklen_t client_size;
    struct sockaddr_in server_addr, client_addr;
    pthread_t workers[THREADCOUNT];
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    
    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Bind to the set port and IP:
    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");
    
    // Listen for clients:
    if (listen(socket_desc, 1) < 0){
        printf("Error while listening\n");
        close(socket_desc);
        return -1;
    }
    
    while (1)
    {
        printf("\nListening for incoming connections.....\n");
        // Accept an incoming connection:
        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
        
        if (client_sock < 0){
            printf("Can't accept\n");
            close(socket_desc);
            close(client_sock);
            return -1;
        }
        printf("Client connected at IP: %s and port: %i\n", 
                     inet_ntoa(client_addr.sin_addr), 
                     ntohs(client_addr.sin_port));
        
        int workerIndex = -1;
        for (int i = 0; i < THREADCOUNT; i++)
        {
            if (clientData[i].inUse == 0)
            {
                workerIndex = i;
                break;
            }
        }
        if (workerIndex == -1)
        {
            printf("Rejected client for having no available threads.\n");
            char* message = "All threads are busy. Please try again later.\n";
            send(client_sock, message, strlen(message), 0);
            continue;
        }
        
        printf("Using worker thread %i",  workerIndex);
        clientData[workerIndex].inUse = 1;
        
        // Create the data to pass to the worker
        clientData[workerIndex].clientSock = client_sock;
        clientData[workerIndex].socketDesc = socket_desc;

        // Receive client's message:
        if (recv(client_sock, clientData[workerIndex].clientMessage, 
                         sizeof(clientData[workerIndex].clientMessage), 0) < 0){
            printf("Couldn't receive\n");
            close(client_sock);
            close(client_sock);
        }
        else
        {
            pthread_create(&workers[workerIndex], NULL, worker, &workerIndex);
        }
    }
    
    // Closing the socket:
    close(client_sock);
    close(socket_desc);
    return 0;
}
