#ifndef UTIL_H
    #define UTIL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERROR -1
#define SUCCESS 0

#define true 1      // Valore booleano TRUE
#define false 0     // Valore booleano FALSE

typedef enum MESSAGE_TYPE{
    SUCCESS_M,      // Operazione eseguita con successo
    ERROR_M,        // Errore non fatale
    WARNING_M,      // Errore che implica la terminazione del programma
    INFO_M,         // Informazione generica 
    MESSAGE_M       // Messaggio rivecuto dal client / server
}MESSAGE_TYPE;

typedef struct operation{
    int32_t op;     // Operatore
    int32_t a;      // Primo operando
    int32_t b;      // Secondo operando
}operation;

/* Visualizzazione messaggi a schermo */
void printMessage(char* message, MESSAGE_TYPE type);

/* Converte il char in ingresso in un integer */
int chartoint(char c);

/* Converte l'integer in ingresso in un char */
char inttochar(int i);

/* Lettura dallo stdin della struct operation */
operation readOperation();

/*Lettura singolo char dallo stdin */
char readChar(char* message);

/*Lettura integer dallo stdin */
int readInt(char* message);

#endif