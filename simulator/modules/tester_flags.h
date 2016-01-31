/*
	Representação do testador de flags
*/

#ifndef TESTER_FLAGS_H
#define TESTER_FLAGS_H

#include "../../lib/string.h"

#include "mx_pc.h"

struct TESTER_FLAGS {
	char *input_OSCZ; 	//OSCZ: Ponteiro para os sinal de saída OSCZ do registrador de flags
	char *cond;			//COND: Ponteiro para o sinal de saída I[14:12] da memória de instruções

    char output; 		//Saída do teste, 1-verdadeiro, 0-falso
};
typedef struct TESTER_FLAGS TF;

extern TF tf;

/*
	Função que representa o sinal OP_TF da unidade de controle. Se 'value' for 1, a saída será
	verdadeira se a condição for verdadeira. Se 'value' for 0, a saída será verdadeira se a
	condição for falsa
*/
void OP_TF(char *value);

/*
	Função que reseta á memória de dados através do sinal RST_TF da unidade de controle.
	Se 'value' for 1, a saída será zerada
*/
void RST_TF(char value);

#endif