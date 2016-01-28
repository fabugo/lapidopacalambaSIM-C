/*
	Representação do registrador de flags
*/

#ifndef REGISTER_FLAGS_H
#define REGISTER_FLAGS_H

#include "../../lib/string.h"

#include "alu.h"

struct REGISTER_FLAGS {
	char *input_flags;		//O, S, C, Z: Ponteiro para os sinais de saída de flags
							//da unidade lógica e aritmética
    char output_flags[4];	//Saída das flags atualziadas
};
typedef struct REGISTER_FLAGS RF;

extern RF rf;

/*
	Função que representa o sinal W_RF da unidade de controle. O parâmetro value indica qual(s)
	flags serão atualizadas
*/
void W_RF(char *value);

/*
	Função que reseta o registrador de flags através do sinal RST_RF da unidade de controle.
	Se 'value' for 1, todas as saídas do registrador de flags será 0.
*/
void RST_RF(char value);

#endif