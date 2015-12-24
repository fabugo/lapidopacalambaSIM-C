/*
	Representação do testador de flags
*/

#ifndef TESTER_FLAGS_H
#define TESTER_FLAGS_H

#include "../../lib/string.h"

#include "register_flags.h"
#include "memory_instruction.h"

struct TESTER_FLAGS {
	int *input_flags; //O, S, C, Z
    char *cond; //Flags que serão atualizadas
    int output; //Saída do teste, 1-verdadeiro, 0-falso
};
typedef struct TESTER_FLAGS TF;

extern TF tf;

//Função para inicializar a struct tf
void TF_start();

/*
	Função que representa o sinal OP_TF da unidade de controle. Se 'value' for 1, a saída será
	verdadeira se a condição for verdadeira. Se 'value' for 0, a saída será verdadeira se a
	condição for falsa
*/
void OP_TF(int value);

#endif