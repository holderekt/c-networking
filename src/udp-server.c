#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
 #include <unistd.h>
#include "../include/sockapi.h"
#include "../include/util.h"



int main(char argc, char *argv[]) {

    // Inizializzazone Socket API (WIN32)
    if(initSocketAPI() != SUCCESS){
        printMessage("Something went wrong during WSA startup", ERROR_M);
        return ERROR;
    }else{
        printMessage("Socket API initialized", SUCCESS_M);
    }

    string hostname = createString(1024);
    gethostname(hostname, 1024);
    struct hostent* myself = gethostbyname(hostname);
    struct in_addr* aaa = (struct in_addr*)myself->h_addr_list[0];

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int server_port  = DEFAULT_PORT;

    // Gestione argomenti in input
    if(argc == 2){
        server_port = atoi(argv[1]);
    }else if (argc > 2){
        printMessage("Argomenti in input non validi", ERROR_M);
        return ERROR;
    }

    // Creazione e configurazione socket server
    if((server_socket = createSocket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == ERROR){
        printMessage("Creazione e configurazione socket", ERROR_M);
        return ERROR;
    }

    // Creazione address del server
    server_address = createAddress_inaddr(AF_INET, aaa, server_port);

    // Binding socket all'address specificato
    if(bindSocket(server_socket, server_address) < 0){
        printMessage("Impossibile eseguire bind all'indirizzo specificato", ERROR_M);
        closeSocket(server_socket);
        return ERROR;
    }else{
        printMessage("Bind eseguito", SUCCESS_M);

    }

    puts("");
    printMessage("Server ora attivo", INFO_M);
    printMessage("Attendo una connessione...", INFO_M);
    puts("");

    // Main loop
    unsigned int clientLength;
    unsigned long int messageSize;
    string test = createString(1024);

    while(true){
        clientLength = sizeof(client_address);
        messageSize = recvfrom(server_socket, test, 1024, 0, (struct sockaddr*)&client_address, &clientLength);
        if(messageSize > 0){
            printMessage(test, INFO_M);
            struct hostent* mario = gethostbyaddr((char*)&client_address.sin_addr, 4, AF_INET);
            struct in_addr* server_in_address = (struct in_addr*) mario->h_addr_list[0];
            printf("Mario: %s ___ %s -- %s\n", mario->h_name, inet_ntoa(*server_in_address), test);
            sendto(server_socket, "OK\0", 3, 0, (struct sockaddr*)&client_address, sizeof(client_address));
        } 

        char c = ' ';
        do{
        
            messageSize = recvfrom(server_socket, &c, sizeof(char), 0, (struct sockaddr*)&client_address, &clientLength);
            if(messageSize > 0){
                if(c != '\0'){
                    c = toupper(c);
                    sendto(server_socket, &c, sizeof(char), 0, (struct sockaddr*)&client_address, sizeof(client_address));
                }
            }
        }while(c != '\0');
    }
       
    
    closeSocket(server_socket);
    return SUCCESS;
}


