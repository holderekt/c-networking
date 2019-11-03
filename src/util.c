#include "../include/util.h"

void printMessage(char* message, MESSAGE_TYPE type){
    char type_message[20];

    switch (type)
    {
    case WARNING_M:
        strcpy(type_message,"[ WARNING]");
        break;
    case ERROR_M:
        strcpy(type_message,"[   ERROR]");
        break;
    case SUCCESS_M:
        strcpy(type_message,"[ SUCCESS]");
        break;
    case INFO_M:
        strcpy(type_message,"[    INFO]");
        break;
    case MESSAGE_M:
        strcpy(type_message,"[ MESSAGE]");
        break;
    }

    
    printf("%s: %s\n", type_message, message);
}

int chartoint(char c){
    return c - '0';
}

char inttochar(int i){
    return i + '0';
}

operation readOperation(){
    char temp;
    operation op;
  
    temp = readChar("Operazione: ");
    temp = tolower(temp);
    op.op = chartoint(temp);
    
    op.a = readInt("A: ");
    op.b = readInt("B: ");

    return op;
}

char readChar(char* message){
    char buffer[512];

    do{
        printf("%s", message);
        fgets(buffer, 512, stdin);
    }while((strlen(buffer) - 1) > 1 || (strlen(buffer) - 1) <= 0);

    return buffer[0];
}

int readInt(char* message){
    int number;
    printf("%s", message);
    scanf("%d", &number);
    return number;
}

