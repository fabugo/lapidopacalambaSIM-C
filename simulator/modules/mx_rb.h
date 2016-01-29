/*
	Representação do multiplexador mx_rb
*/

#ifndef MX_RB_H
#define MX_RB_H

#include <string.h>

#include "../defs.h"
#include "../../lib/string.h"

struct MX_RB {
    char *input_PC;	//Ponteiro para o sinal de saída do contador de programa
    char *input_DM;	//Ponteiro para o sinal de saída PR da memória de dados
    char *input_ALU;//Ponteiro para o sinal de saída C da unidade lógica e aritmética

    char output[33];//Saída selecionada pelo sinal S_MXRB
};
typedef struct MX_RB MX_RB;

extern MX_RB mx_rb;

/*
	Função que representa o sinal S_MXRB da unidade de controle. Se 'value' for 00,
	o conteúdo da entrada input_PC será selecionada para a saída. Caso seja 01, será
	selecionada a entrada input_DM. Por último, caso seja 10, a entrada input_ALU será
	selecionada;
*/
void S_MXRB(char *value);

#endif