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

typedef char* string;

typedef enum MESSAGE_TYPE{
    SUCCESS_M   = 0,      // Operazione eseguita con successo
    ERROR_M     = 1,      // Errore non fatale
    WARNING_M   = 2,      // Errore che implica la terminazione del programma
    INFO_M      = 3,      // Informazione generica 
    MESSAGE_M   = 4,      // Messaggio rivecuto dal client / server
    INPUT_M     = 5       // Input utente
}MESSAGE_TYPE;

typedef struct operation{
    int32_t op;     // Operatore
    int32_t a;      // Primo operando
    int32_t b;      // Secondo operando
}operation;

extern const string BYTE_PRINT_FORMAT[2];
extern const string MESSAGES[6];

/* Visualizzazione messaggi a schermo */
void printMessage(string message, MESSAGE_TYPE type);

/* Visualizzazione tipologia messaggio a schermo */
void printType(MESSAGE_TYPE type);

/* Converte il char in ingresso in un integer */
int chartoint(char c);

/* Converte l'integer in ingresso in un char */
char inttochar(int i);

/*Lettura singolo char dallo stdin */
char readChar(string message);

/*Lettura integer dallo stdin */
int readInt(string message);

/* Allocazione stringa */
string createString(unsigned long size);

/* Lettura dallo stdin della struct operation */
operation readOperation();

/* Lettura stringa da tastiera */
string readLine(unsigned long int size);

/* True se il carattere è una vocale */
int isVowel(char c);

#endif


