#include "../include/sockapi.h"

int initSocketAPI(){
    #if defined WIN32
        WSADATA wsadata;
        if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0){
            return ERROR;
        }
    #endif

    return SUCCESS;
}

void closeSocket(int socket){ 
    #if defined WIN32
        closesocket(socket);
        WSACleanup();
    #else
        close(socket);
    #endif
}

int bindSocket(int socket, struct sockaddr_in address){
    return bind(socket, (struct sockaddr*)&address, sizeof(address));
}

int acceptClientSocket(int server_socket, struct sockaddr_in client_address){
    int client_len = sizeof(client_address);
    return accept(server_socket, (struct sockaddr*)&client_address, (socklen_t*)&client_len);
}

struct sockaddr_in createAddress(int family, char* ip, short int port){
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = family;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    return address;
}

int createSocket(int domain, int type, int protocol){
    int new_socket = socket(domain, type, protocol);
    int true_value = 1;

    if(new_socket < 0){
        return ERROR;
    }else if(setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &true_value, sizeof(true_value)) != 0){
        return ERROR;
    }else{
        return new_socket;
    }
}

int sendData(int destination_socket, void* data, size_t data_size){
    if((send(destination_socket, data, data_size, 0) != data_size)){
        return ERROR;
    }
    return data_size;
}  

char* receiveMessage(int socket){
    char buffer[DEFAULT_BUFFER];
    int valread = recv(socket, buffer, DEFAULT_BUFFER, 0);

    if(valread > 0){
        buffer[valread] = '\0';
    }else{
        return NULL;
    }

    char *result = (char *) malloc(sizeof(char) * strlen(buffer));
    strcpy(result, buffer);

    return result;
}

int sendOperation(int destination_socket, operation operation){
    operation.op = htonl(operation.op);
    operation.a = htonl(operation.a);
    operation.b = htonl(operation.b);
    return sendData(destination_socket, &operation, sizeof(operation));
}

int receiveOperation(int socket, operation *operation){
     if(recv(socket, operation, sizeof(*operation), 0) != ERROR){
        operation->a = ntohl(operation->a);
        operation->b = ntohl(operation->b);
        operation->op = ntohl(operation->op);
        operation->op = inttochar(operation->op);
        return SUCCESS;
     }

     return ERROR;
}

char* generateOperationMessage(operation op){
    char buffer[DEFAULT_BUFFER] = "";

    switch(tolower((char)op.op)){
        case 'a':
            sprintf(buffer, "Risultato della addizione %d + %d = %f\0", op.a, op.b, (double)(op.a + op.b));
            break;
        case 's':
            sprintf(buffer, "Risultato della sottrazione%d - %d = %f\0", op.a, op.b, (double)(op.a - op.b));
            break;
        case 'd':
            if(op.b == 0){
                    sprintf(buffer, "Risultato della divisione %d / %d = error\0", op.a, op.b);
            }else{
                    sprintf(buffer, "Risultato della divisione %d / %d = %f\0", op.a, op.b, (double)(op.a / op.b));
            }
            break;
        case 'm':
            sprintf(buffer, "Risultato della moltiplicatione %d + %d = %f\0", op.a, op.b, (double)(op.a * op.b));
            break;

        default:
            strcpy(buffer, TERMINATION_MESSAGE);
    }

    char* result_message = (char *) malloc(sizeof(char) * strlen(buffer));
    strcpy(result_message, buffer);
    return result_message;
}
