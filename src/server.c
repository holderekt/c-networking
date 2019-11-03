#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sockapi.h"
#include "../include/util.h"



int main(char argc, char *argv[]) {

    // Socket API initialization
    if(initSocketAPI() != SUCCESS){
        printMessage("Something went wrong during WSA startup", ERROR_M);
        return ERROR;
    }else{
        printMessage("Socket API initialized", SUCCESS_M);
    }

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int server_port  = DEFAULT_PORT;

    // Port number from program arguments
    if(argc == 2){
        server_port = atoi(argv[1]);
    }else if (argc > 2){
        printMessage("Only one argument is accepted", ERROR_M);
        return ERROR;
    }

    // Socket creation and configuration
    if((server_socket = createSocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == ERROR){
        printMessage("Creazione e configurazione socket", ERROR_M);
        return ERROR;
    }

    // Server address creation
    server_address = createAddress(AF_INET, LOCALHOST, server_port);

    // Socket Bind
    if(bindSocket(server_socket, server_address) < 0){
        printMessage("Cannot bind socket to given address", ERROR_M);
        closeSocket(server_socket);
        return ERROR;
    }else{
        printMessage("Bind socket to address", SUCCESS_M);

    }

    struct sockaddr_in aaa;
    int size = sizeof(aaa);

    // Socket on listen
    if(listen(server_socket, DEFAULT_QLEN ) < 0){
        printMessage("Listen", ERROR_M);
        closeSocket(server_socket);
        return ERROR;
    }else{
        char message[100] = "Socket listening on port ";
        char port[6];
        sprintf(port, "%d", server_port);
        strcat(message, port);
        printMessage(message, SUCCESS_M);
    }

    puts("");
    printMessage("Server now active", INFO_M);
    printMessage("Waiting connection", INFO_M);
    puts("");

    while(true){
       
        if((client_socket = acceptClientSocket(server_socket, client_address)) < 0){
            printMessage("Accepting client", ERROR_M);
            closeSocket(server_socket);
            return ERROR;
        }

        char message[DEFAULT_BUFFER] = "Connessione Avvenuta";

        if(sendData(client_socket, message, strlen(message)) == ERROR){
            printMessage("Message sent with errors", WARNING_M);
        }else{
            printMessage("Message sent", SUCCESS_M);
        }


        operation op;

        if(receiveOperation(client_socket, &op) != SUCCESS){
            printMessage("Ricezione operazione fallita", WARNING_M);
            closeSocket(client_socket);
            continue;
        }else{
            
            char* operation_result = generateOperationMessage(op);

            if(sendData(client_socket, operation_result, strlen(operation_result)) == ERROR){
                printMessage("Message sent with errors", WARNING_M);
            }else{
                printMessage("Message sent", SUCCESS_M);
            }
        }

    
        closeSocket(client_socket);
    }

    return SUCCESS;
}


