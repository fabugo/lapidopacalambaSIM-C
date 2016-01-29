/*
	Representação do banco de registradores
*/

#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include <string.h>

#include "../defs.h"
#include "../../lib/string.h"

struct REGISTER_BANK {
    char *input_RA; //RA: Ponteiro para o sinal de saída I[19:16] da memória de instruções
                    //Endereço para o registrador A a ser lido
    char *input_RB; //RB: Ponteiro para o sinal de saída I[15:12] da memória de instruções
                    //Endereço para o registrador B a ser lido
    char *input_WC; //WC: Ponteiro para o sinal de saída I[23:20] da memória de instruções
                    //Endereço para o registrador C a ser escrito
    char *input_WPC; //WPC: Ponteiro para o sinal de saída do multiplexador MR_RB

    char output_PRA[33]; //PRA: Saída do dado lido do registrador indicado por RA
    char output_PRB[33]; //PRB: Saída do dado lido do registrador indicado por RB

    char registers[RB_SIZE][33]; //Matriz de 'RB_SIZE' registradores de 32 bits
};
typedef struct REGISTER_BANK R_BANK;

extern R_BANK rbank;

/*
	Função que representa o sinal W_RB da unidade de controle. O parâmetro value indica se a
	operação é de escrita (valor 1) ou leitura (valor 0)
*/
void W_RB(char value);

/*
	Função que reseta o banco de registradores através do sinal RST_RB da unidade de controle.
	Se 'value' for 1, as saidas PRA e PRB assim como todos os registradores terão seus valores
	zerados
*/
void RST_RB(char value);

#endif