#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sockapi.h"
#include "../include/util.h"

int main(char argc, char *argv[]) {

    // Inizializzazone Socket API (WIN32)
    if(initSocketAPI() != 0){
        printMessage("Impossibile inizializzare WINSOCK", ERROR_M);
        return ERROR;
    }else{
        printMessage("Socket API inizializzata", SUCCESS_M);
    }

    int client_socket;
    struct sockaddr_in server_address;
    char* server_saddr;
    int server_port;

    if((client_socket = createSocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printMessage("Impossibile creare il socket client", ERROR_M);
        return ERROR;
    }

    // Argomenti in input 
    if(argc == 3){
        server_saddr = argv[1];         // Indirizzo server
        server_port = atoi(argv[2]);    // Porta server
    }else{
        printMessage("Argomenti in input non validi", ERROR_M);
        closeSocket(client_socket);
        return ERROR;
    }
    
    // Creazione address server 
    server_address = createAddress(AF_INET, server_saddr, server_port);

    // Connessione client al server
    if((connectSocket(client_socket, server_address)) < 0){
        printMessage("During server connection", ERROR_M);
        closeSocket(client_socket);
        return ERROR;
    }

    // Ricezione messaggio connessione avvenuta
    char *message = receiveMessage(client_socket);
    printMessage(message, MESSAGE_M);


    // Lettura dati operazione
    printMessage("Inserimento dati operazione...", INFO_M);
    operation op = readOperation();
    

    // Invio dati operazione 
    if(sendOperation(client_socket, op) == ERROR){
        printMessage("Errore nell'invio dati", WARNING_M);
    }

    // Ricezione messaggio elaborazione operazione
    char *operation_result = receiveMessage(client_socket);
    if(strcmp(operation_result, TERMINATION_MESSAGE) == 0){
        printMessage("Chiusura connessione", INFO_M);
    }else{
        printMessage(operation_result, MESSAGE_M);
    }

    printMessage("Chiusura socket", INFO_M);
    closeSocket(client_socket);

    return SUCCESS;
}