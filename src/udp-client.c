#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sockapi.h"
#include "../include/util.h"
#include <netdb.h>

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

    if((client_socket = createSocket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
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

    // Ricerco indirizzo server da hostname
    struct hostent* server_hostent = gethostbyname(server_saddr);
    struct in_addr* server_in_address;

    if(server_hostent != NULL){
        
        server_in_address = (struct in_addr*) server_hostent->h_addr_list[0];

        if(server_in_address != NULL){

            // Visualizzo informazioni server

            string message = createString(1024);
            strcpy(message, "Connessione al server: ");
            strcat(message, server_hostent->h_name);
            printMessage(message, INFO_M);

            strcpy(message, "Indirizzo server: ");
            strcat(message, inet_ntoa(*server_in_address));
            printMessage(message, INFO_M);
        }else{
            printMessage("Errore indirizzo ip server", ERROR_M);
            return ERROR;
        }     
    }else{
        printMessage("Errore nome host inserito", ERROR_M);
        return ERROR;
    }
    
    // Creazione address server 
    server_address = createAddress_inaddr(AF_INET, server_in_address, server_port);

    // Invio messaggio inizio connessione
    sendto(client_socket, INITIALIZATION_MESSAGE, DEFAULT_BUFFER, 0, (struct sockaddr*)&server_address, sizeof(server_address));
    
    // Ricezione risposta server
    string recvmessage = createString(DEFAULT_BUFFER);
    unsigned long int messagesize;
    unsigned int address_len = sizeof(server_address);
    messagesize = recvfrom(client_socket, recvmessage, DEFAULT_BUFFER, 0, (struct sockaddr*)&server_address, &address_len);
    
    if(messagesize > 0){
        printMessage(recvmessage, MESSAGE_M);
    }else{
        printMessage("Nessun messaggio ricevuto", ERROR_M);
        return ERROR;
    }

    // Lettura stringa da tastiera 
    printType(INPUT_M);
    string message = readLine(1024);
    int vowelcount = 0;
    for(int i=0; i!= strlen(message); i++){
        // Conteggio vocali e invio vocale al server
        if(isVowel(message[i])){
            sendto(client_socket, &(message[i]), sizeof(char), 0, (struct sockaddr*)&server_address, sizeof(server_address));
            vowelcount++;
        }
    }

    // Invio carattere terminazione al server
    char sendstop = '\0';
    sendto(client_socket, &sendstop, sizeof(sendstop) , 0, (struct sockaddr*)&server_address, sizeof(server_address));

    // Ricezione vocali dal server e stampa
    uint32_t letter;
    string vowelmessage = createString(vowelcount + 1);
    strcpy(vowelmessage, "");

    for(int i=0; i!=vowelcount; i++){
        messagesize = recvfrom(client_socket, &letter, sizeof(uint32_t), 0, (struct sockaddr*)&server_address, &address_len);
        if(messagesize > 0){
            vowelmessage[i] = letter;
        }else{
            printMessage("Nessun messaggio ricevuto", ERROR_M);
            return ERROR;
        }
    }
    
    vowelmessage[vowelcount] = '\0';
    printMessage(vowelmessage, MESSAGE_M);

    printMessage("Chiusura socket", INFO_M);
    closeSocket(client_socket);
    
    return SUCCESS;
}