/*
	Representação do multiplexador mx_pc
*/

#ifndef ADD_H
#define ADD_H

#include <string.h>

#include "alu.h"

struct ADD {
    char *input; 	//Ponteiro para o sinal de saída do contador de programa

    char output[33];	//Saída incrementada
};
typedef struct ADD ADD;

extern ADD add;

/*
	Função que incrementa o valor de pc;
*/
void ADD_PC(char value);

#endif