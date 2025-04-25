/*
 * rfs.c -- TCP Socket Client / Practicum 2 / Program in C
 * 
 * Liz Kiefer / CS5600 / Northeastern University
 * Fall 2024 / Dec 1, 2024
 * adapted from: 
 *   https://www.educative.io/answers/how-to-implement-tcp-sockets-in-c
 */
 
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Prints hints for program usage
void printUsage()
{
    printf("Not enough arguments received! Allowed commands are:\n");
    printf("WRITE: Read a local file and write its contents on the remote file server\n");
    printf("Requires the name of the local file, then the name of the file to create on the remote file server\n");
    printf("Example: rfs WRITE data/localfoo.txt folder/foo.txt\n");
    printf("GET: Read a file's contents on the remote file server, then write its contents locally\n");
    printf("Requires the name of the file on the remote file server, then the name of the local file to create\n");
    printf("Example: rfs GET remote_folder/remote_file.html local_folder/local_file.html\n");
    printf("RM: Remove a file on the remote file server\n");
    printf("Requires the name of the file on the remote file serve to remove\n");
    printf("Example: rfs RM folder/somefile.txt\n");
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        printUsage();
        return -1;
    }
    
    char server_message[8196];
    char client_message[8192];
    char* fileMode;
    if (strcmp(argv[1], "WRITE") == 0)
    {
        if (argc < 4) {
            printUsage();
            return -1;
        }
        strcat(client_message, "w");
        strcat(client_message, "\n");
        strcat(client_message, argv[3]); // Name of remote file to create on server
        strcat(client_message, "\n");
        
        // Read local file and add it to the client string
        FILE *localFile = fopen(argv[2], "r");
        char line[1024] = "";
        while (fgets(line, sizeof(line), localFile))
        {
            strcat(client_message, line);
        }
    }
    else if (strcmp(argv[1], "GET") == 0)
    {
        if (argc < 4) {
            printUsage();
            return -1;
        }
        strcat(client_message, "r");
        strcat(client_message, "\n");
        strcat(client_message, argv[2]); // Name of remote file to read on server
        strcat(client_message, "\n");
    }
    else if (strcmp(argv[1], "RM") == 0)
    {
        strcat(client_message, "d");
        strcat(client_message, "\n");
        strcat(client_message, argv[2]); // Name of remote file to remove
    }
    else
    {
        printf("Invalid file operation. Options are: WRITE, GET, RM\n");
        return -1;
    }
    
    int socket_desc;
    struct sockaddr_in server_addr;

    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0){
        printf("Unable to create socket\n");
        close(socket_desc);
        return -1;
    }

    printf("Socket created successfully\n");

    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send connection request to server:
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        close(socket_desc);
        return -1;
    }
    printf("Connected with server successfully\n");
    
    // Send the message to server:
    if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
        printf("Unable to send message\n");
        close(socket_desc);
        return -1;
    }

    // Receive the server's response:
    if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
        printf("Error while receiving server's msg\n");
        close(socket_desc);
        return -1;
    }
    
    if (strcmp(argv[1], "WRITE") == 0)
    {
        printf("Server's response: %s\n", server_message);
    }
    else if (strcmp(argv[1], "GET") == 0)
    {
        char *line;
        // First line of return indicates success or failure with a 0 or error message
        line = strtok(server_message, "\n");
        // Write incoming data to local file
        if (strcmp(line, "0") == 0) {
            line = strtok(NULL, "\n");
            FILE *localFile = fopen(argv[3], "w");
            while (line != NULL) {
                fprintf(localFile, "%s\n", line);
                line = strtok(NULL, "\n");
            }
            fclose(localFile);
            printf("Successfully wrote to local file %s\n", argv[3]);
        }
        else
        {
            // Failure returned, print message
            printf("Server's response: %s\n", line);
            close(socket_desc);
            return -1;
        }
    }
    else if (strcmp(argv[1], "RM") == 0)
    {
        printf("Server's response: %s\n", server_message);
    }

    // Close the socket:
    close(socket_desc);

    return 0;
}
