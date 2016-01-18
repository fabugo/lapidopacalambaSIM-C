/*
	Representação do contador de programa
*/

#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include <string.h>
#include "../defs.h"

struct PROGRAM_COUNTER {
    char input[33];
    char output[33]; //Endereço da próxima instrução
};
typedef struct PROGRAM_COUNTER PC;

extern PC pc;

//Função para inicializar a struct pc
void PC_start();

/*
	Função que representa o sinal W_PC da unidade de controle. Se 'value' for 1, o
	valor de 'input' é passado para 'output'
*/
void W_PC(int value);

/*
	Função que reseta o contador de programa através do sinal RST_PC da unidade de controle.
	Se 'value' for 1, a saida 'output' receberá o valor 0.
*/
void RST_PC(int value);

#endif