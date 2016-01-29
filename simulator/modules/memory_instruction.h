/*
	Representação da memória de instruções
*/

#ifndef MEMORY_INSTRUCTION_H
#define MEMORY_INSTRUCTION_H

#include <string.h>

#include "../defs.h"
#include "../../lib/string.h"

struct MEMORY_INSTRUCTION {
	char *input; 					//RI: Ponteiro para o sinal da saída do contador de programa

	char output[33]; 				//I: Próxima instrução a ser executada
	
    char instruction[MI_SIZE][33]; 	//Matriz contendo até 'MI_SIZE' instruções de 32 bits
};
typedef struct MEMORY_INSTRUCTION MI;

extern MI mi;

/*
	Função que representa o sinal W_MI da unidade de controle. Se 'value' for 1, o conteúdo
	do endereço indicado por 'input' será lido e posto na saída 'output';
*/
void W_MI(char value);

/*
	Função que reseta a memória de instruções através do sinal RST_MI da unidade de controle.
	Se 'value' for 1, a saída assim como toda a memória de instruções serão zeradas
*/
void RST_MI(char value);

#endif