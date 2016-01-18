/*
	Representação do extensor de sinal
*/

#ifndef SIGNAL_EXTENDER_H
#define SIGNAL_EXTENDER_H

#include <stdio.h>
#include "../defs.h"
#include "../../lib/string.h"

#include "memory_instruction.h"

struct SIGNAL_EXTENDER {
    char *input;
    char output[33]; //Saída extendida
};
typedef struct SIGNAL_EXTENDER SE;

extern SE se;

//Função para inicializar a struct se
void SE_start();

/*
	Função que representa o sinal OP_SE da unidade de controle. Se 'value' for 1, a saída
	será a extensão dos 16 bits menos significativos da entrada. Caso sejá 0, a saída será
	a extensão dos 12 bits menos significativos.
*/
void OP_SE(int value);

#endif