#ifndef UTIL_H
    #define UTIL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERROR -1
#define SUCCESS 0

#define true 1
#define false 0

typedef enum MESSAGE_TYPE{
    WARNING_M, 
    ERROR_M, 
    SUCCESS_M,
    INFO_M,
    MESSAGE_M
}MESSAGE_TYPE;

typedef struct operation{
    int32_t op;
    int32_t a;
    int32_t b;
}operation;

void printMessage(char* message, MESSAGE_TYPE type);
int chartoint(char c);
char inttochar(int i);
char* inttostring(int integer);
operation readOperation();
char readChar(char* message);
int readInt(char* message);

#endif