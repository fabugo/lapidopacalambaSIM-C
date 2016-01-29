/*
	Representação da unidade lógica e aritmética
*/

#ifndef ALU_H
#define ALU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../defs.h"
#include "../../lib/string.h"

struct ALU {
    char *input_A; 	//A: Ponteiro para o sinal de saída PRA do banco de registradores
    char *input_B; 	//B: Ponteiro para o sinal de saída do multiplexador MX_SE

    char output[33];//C: Saída do resultado da operação feita.
    char flags[4]; 	//F: Saída para os sinais de flags: O, S, C, Z
};
typedef struct ALU ALU;

extern ALU alu;

/*
	Função que representa o sinal OP_ALU da unidade de controle. Ele contém 5 bits e indica
	qual operação será realizada pela unidade lógica aritmética.
*/
void OP_ALU(char *value);

/*
	Função que reseta á memória de dados através do sinal RST_ALU da unidade de controle.
	Se 'value' for 1, a saída da operação e as saídas de flags serão zeradas
*/
void RST_ALU(char value);

#endif