#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sockapi.h"
#include "../include/util.h"

int main(char argc, char *argv[]) {

    // Socket API initialization

    if(initSocketAPI() != 0){
        printMessage("Something went wrong during WSA startup", ERROR_M);
        return ERROR;
    }else{
        printMessage("Socket API initialized", SUCCESS_M);
    }

    int client_socket;
    struct sockaddr_in server_address;

    if((client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printMessage("Socket creation", ERROR_M);
        return ERROR;
    }

    char* server_ip = argv[1];
    int server_port = atoi(argv[2]);

    printf("%s :: %d\n", server_ip, server_port);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(server_port);

    if(connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        printMessage("During server connection", ERROR_M);
        return ERROR;
    }


    char *message = receiveMessage(client_socket);
    printMessage(message, MESSAGE_M);

    printMessage("Input operation data...", INFO_M);

    operation op = readOperation();
    
    if(sendOperation(client_socket, op) == ERROR){
        printMessage("Errore nell'invio dati", WARNING_M);
    }

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