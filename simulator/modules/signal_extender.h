/*
	Representação do extensor de sinal
*/

#ifndef SIGNAL_EXTENDER_H
#define SIGNAL_EXTENDER_H

#include <stdio.h>

#include "../defs.h"
#include "../../lib/string.h"

struct SIGNAL_EXTENDER {
    char *input;	//Ponteiro para o sinal de saída I[0:15]/[0:11] da memória de instruções

    char output[33];//Saída extendida de 32 bits dos 16 ou 12 bits de entrada
};
typedef struct SIGNAL_EXTENDER SE;

extern SE se;

/*
	Função que representa o sinal OP_SE da unidade de controle. Se 'value' for 1, a saída
	será a extensão dos 16 bits menos significativos da entrada. Caso sejá 0, a saída será
	a extensão dos 12 bits menos significativos.
*/
void OP_SE(char value);

/*
	Função que reseta á memória de dados através do sinal RST_SE da unidade de controle.
	Se 'value' for 1, a saída será zerada
*/
void RST_SE(char value);

#endif