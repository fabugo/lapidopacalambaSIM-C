/*
	Representação do registrador de flags
*/

#ifndef REGISTER_FLAGS_H
#define REGISTER_FLAGS_H

#include "alu.h"

struct REGISTER_FLAGS {
	//Ponteiro para a saida de flags da alu
	int *input_flags; //O, S, C, Z
    int output_flags[4]; //O, S, C, Z
};
typedef struct REGISTER_FLAGS RF;

extern RF rf;

//Função que inicializa a struct rf
void RF_start();

/*
	Função que representa o sinal W_RF da unidade de controle. O parâmetro value indica qual(s)
	flags serão atualizadas
*/
void W_RF(int value);

/*
	Função que reseta o registrador de flags através do sinal RST_RF da unidade de controle.
	Se 'value' for 1, todas as saídas do registrador de flags será 0.
*/
void RST_RF(int value);

#endif