/*
	Representação do contador de programa
*/

#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include <string.h>

#include "../defs.h"

struct PROGRAM_COUNTER {
    char *input;	//Ponteiro para o sinal de saída do multiplexador MX_PC
    
    char output[33];//Endereço da próxima instrução a ser executada
};
typedef struct PROGRAM_COUNTER PC;

extern PC pc;

/*
	Função que representa o sinal W_PC da unidade de controle. Se 'value' for 1, o
	valor de 'input' é passado para 'output'
*/
void W_PC(char value);

/*
	Função que reseta o contador de programa através do sinal RST_PC da unidade de controle.
	Se 'value' for 1, a saida 'output' receberá o valor 0.
*/
void RST_PC(char value);

#endif