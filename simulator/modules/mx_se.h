/*
	Representação do multiplexador mx_se
*/

#ifndef MX_SE_H
#define MX_SE_H

#include <string.h>

#include "../defs.h"

struct MX_SE {
    char *input_RB;	//Ponteiro para o sinal de saída PRB do banco de registradores
    char *input_SE;	//Ponteiro para o sinal de saída do extensor de sinal

    char output[33];//Saída selecionada pelo sinal S_MXSE
};
typedef struct MX_SE MX_SE;

extern MX_SE mx_se;

/*
	Função que representa o sinal S_MXPC da unidade de controle. Se 'value' for 0,
	o conteúdo da entrada input_RB será selecionada para a saída. Caso seja 1, será
	selecionada a entrada input_SE;
*/
void S_MXSE(char value);

#endif