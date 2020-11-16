#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

//DEFINES
//Define the port on which the program is listening
#define PORT 8080
#define LENGTH 1024

//FUNCTIONS
int countBuffer();

//GLOBAL VARIABLES
char buffer[LENGTH];

int main()
{
    int server, valread, newServer, opt = 1;
    struct sockaddr_in serverStruct;
    int addrlen = sizeof(serverStruct);
    ssize_t recievedMessage;

    //Set the socket for the program and check if it failed
    if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("Error: socket");
        return 0;
    }

    /*Certain options fort the socket are set. Options such as the level
    of the paket managment for example.*/
    if(setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        printf("Error: setting socket");
        return 0;
    }

    //Set the trafic for the IPv4
    serverStruct.sin_family = AF_INET;
    //Accept every incoming message
    serverStruct.sin_addr.s_addr = INADDR_ANY;
    //Set the port for the server (in this case 8080)
    serverStruct.sin_port = htons(PORT);

    if(bind(server, (struct sockaddr *)&serverStruct, sizeof(serverStruct)) < 0)
    {
        printf("Error: binding socket");
        return 0;
    }

    //The socket 'listens' on the port and waits for a new connection
    if(listen(server, 3) < 0)
    {
        printf("Error: listening");
        return 0;
    }

    //Wait till the opposite socket accepts the connection
    if((newServer = accept(server, (struct sockaddr *)&serverStruct, (socklen_t*)&addrlen))<0)
    {
        printf("Error: accept");
        return 0;
    }

    //Read the recieved message and store it in the variable buffer-
    recievedMessage = recv(newServer, buffer, LENGTH, 0);
    printf("%s\n", buffer);
    int count = countBuffer();
    //Send the message back.
    send(newServer, buffer, count, 0);

    return 0;
}

//Counts the characters in the buffer
int countBuffer()
{
    int count = 0;

    for(int i = 0; i < LENGTH; i++)
    {
        if(buffer[i]!=NULL)
        {
            count++;
        }
    }
    return count;
}
