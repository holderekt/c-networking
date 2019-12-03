#include "../include/util.h"

const string MESSAGES[6] = {
    "[ SUCCESS]",
    "[   ERROR]",
    "[ WARNING]",
    "[    INFO]",
    "[ MESSAGE]",
    "[   INPUT]"
};

string createString(unsigned long size){
    return (string) malloc(sizeof(char) * size);
}

void printMessage(string message, MESSAGE_TYPE type){    
    printf("%s: %s\n", MESSAGES[type], message);
}

void printType(MESSAGE_TYPE type){
    printf("%s: ", MESSAGES[type]);
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
    
    op.a = readInt("Operando 1: ");
    op.b = readInt("Operando 2: ");

    return op;
}

char readChar(string message){
    char buffer[512];

    do{
        printf("%s", message);
        fgets(buffer, 512, stdin);
    }while((strlen(buffer) - 1) > 1 || (strlen(buffer) - 1) <= 0);

    return buffer[0];
}

int readInt(string message){
    int number;
    printf("%s", message);
    scanf("%d", &number);
    return number;
}

string readLine(unsigned long int size){
    string line = createString(size);
    fgets(line, size, stdin);
    line[strlen(line)] = '\0';
    return line;
}

int isVowel(char c){
    c = tolower(c);
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ){
        return true;
    }

    return false;
}