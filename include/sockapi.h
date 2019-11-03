#ifndef SOCK_API_H
    #define SOCK_API_H


#include <stdio.h>
#include <stdlib.h>
#include "../include/util.h"

#if defined WIN32
    #include <winsock.h>
#else 
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#define LOCALHOST "127.0.0.1"
#define DEFAULT_PORT 8080
#define DEFAULT_QLEN 6
#define DEFAULT_BUFFER 512
#define TERMINATION_MESSAGE "TERMINE PROCESSO CLIENT\0"

int initSocketAPI();
void closeSocket(int socket);
int bindSocket(int socket, struct sockaddr_in address);
int acceptClientSocket(int server_socket, struct sockaddr_in client_address);
struct sockaddr_in createAddress(int family, char* ip, short int port);
int createSocket(int domain, int type, int protocol);
int sendData(int destination_socket, void* data, size_t data_size);
char* receiveMessage(int socket);
int sendOperation(int destination_socket, operation operation);
int receiveOperation(int socket, operation *operation);
char *generateOperationMessage(operation operation);

#endif