/*
	Representação da memória de instruções
*/

#ifndef MEMORY_INSTRUCTION_H
#define MEMORY_INSTRUCTION_H

#include <string.h>
#include "../defs.h"
#include "../../lib/string.h"

#include "program_counter.h"

struct MEMORY_INSTRUCTION {
	char *input; //Endereço da instrução que será lida
	char output[33]; //Instrução lida
    char instruction[MI_SIZE][33]; //Matriz contendo até 'MI_SIZE' instruções de 32 bits
};
typedef struct MEMORY_INSTRUCTION MI;

extern MI mi;

//Função para inicializar a struct mi
void MI_start();

/*
	Função que representa o sinal W_MI da unidade de controle. Se 'value' for 1, o conteúdo
	do endereço indicado por 'input' será lido e posto na saída 'output';
*/
void W_MI(int value);

/*
	Função que reseta a memória de instruções através do sinal RST_MI da unidade de controle.
	Se 'value' for 1, a saída assim como toda a memória de instruções serão zeradas
*/
void RST_MI(int value);

#endif