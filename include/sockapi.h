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

/* Startup WSA (WIN32) */
int initSocketAPI();

/* Chiusura socket e WSA Cleanup (WIN32) */
void closeSocket(int socket);

/* Binding socket all'address specificato */
int bindSocket(int socket, struct sockaddr_in address);

/* Ritorna la socket per la connessione al client in caso di successo.
ERROR altrimenti */
int acceptClientSocket(int server_socket, struct sockaddr_in client_address);

/* Creazione struct indirizzo */
struct sockaddr_in createAddress(int family, char* ip, short int port);

/* Creazione e configurazione socket. Socket impostato per il 
riutilizzo dell'address locale. Ritorna il socket in caso di successo
ERROR altrimenti */
int createSocket(int domain, int type, int protocol);

/* Invia dati generici. Ritorna i byte inviati in caso di successo.
ERROR altrimenti */
int sendData(int destination_socket, void* data, size_t data_size);

/* Riceve un messaggio testuale. Ritorna NULL in caso di errore */
char* receiveMessage(int socket);

/* Invia una scruct operazione. Ritorna i byte inviati in caso di
successo. ERROR altrimenti */
int sendOperation(int destination_socket, operation operation);

/* Rivece i dati dell'operazione. Ritorna ERROR in caso di errore, 
SUCCESS altrimenti */
int receiveOperation(int socket, operation *operation);

/* Elabora l'operazione e ritorna un messaggio contentente il risultato
o un generico messaggio di terminazione connessione */
char *generateOperationMessage(operation operation);

/* Connessione socket all'address specificato */
int connectSocket(int socket, struct sockaddr_in address);

#endif