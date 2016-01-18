/*
	Representação do banco de registradores
*/

#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include <string.h>
#include "../defs.h"
#include "../../lib/string.h"

#include "memory_instruction.h"

struct REGISTER_BANK {
    char *input_RA; //Endereço do registrador A a ser lido
    char *input_RB; //Endereço do registrador B a ser lido
    char *input_WC; //Endereço do registrador C que será escrito
    char *input_WPC; //Dado a ser escrito no registrador indicado por WC

    char output_PRA[33]; //Saída do dado do registrador indicado por RA
    char output_PRB[33]; //Saída do dado do registrador indicado por RB

    char registers[RB_SIZE][33]; //Matriz de 'RB_SIZE' registradores de 32 bits
};
typedef struct REGISTER_BANK R_BANK;

extern R_BANK rbank;

//Função para inicializar a struct rbank
void RB_start();

/*
	Função que representa o sinal W_RB da unidade de controle. O parâmetro value indica se a
	operação é de escrita (valor 1) ou leitura (valor 0)
*/
void W_RB(int value);

/*
	Função que reseta o banco de registradores através do sinal RST_RB da unidade de controle.
	Se 'value' for 1, as saidas PRA e PRB assim como todos os registradores terão seus valores
	zerados
*/
void RST_RB(int value);

#endif