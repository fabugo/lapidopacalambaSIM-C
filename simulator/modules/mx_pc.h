/*
	Representação do multiplexador mx_pc
*/

#ifndef MX_PC_H
#define MX_PC_H

#include <string.h>

struct MX_PC {
    char *input_ALU; 	//Ponteiro para o sinal de saída C da unidade lógica e aritmética
    char *input_ADD; 	//Ponteiro para o sinal de saída do contador de programa

    char output[33];	//Saída selecionada pelo sinal S_MXPC
};
typedef struct MX_PC MX_PC;

extern MX_PC mx_pc;

/*
	Função que representa o sinal S_MXPC da unidade de controle. Se 'value' for 0,
	o conteúdo da entrada input_ALU será selecionada para a saída. Caso seja 1, será
	selecionada a entrada input_PC;
*/
void S_MXPC(char value);

#endif