#ifndef UNIT_CONTROL_H
#define UNIT_CONTROL_H

#include <stdlib.h>
#include <stdio.h>

#include "../defs.h"
#include "../../lib/string.h"

#include "memory_instruction.h"
#include "signal_extender.h"
#include "register_bank.h"
#include "mx_se.h"
#include "alu.h"
#include "data_memory.h"
#include "register_flags.h"
#include "tester_flags.h"
#include "mx_pc.h"
#include "mx_rb.h"
#include "program_counter.h"
#include "add.h"

struct UNIT_CONTROL {
    char *TYPE_OP;	//Ponteiro para o sinal de saída I[31:24] da memória de instruções

    char OP_ALU[6];	//Sinal para a unidade de controle
    char OP_TF[4];	//sinal para o testador de flags
    char W_RB;		//sinal para o banco de registradores
    char W_DM;		//sinal para a memória de dados
    char W_RF[4];	//sinal para o registrador de flags
    char S_MXSE;	//sinal para o multiplexador MX_SE
    char S_MXRB[3];	//sinal para o multiplexador MX_RB
};
typedef struct UNIT_CONTROL UC;

extern UC uc;

/*
	Função para que a unidade de controle inicie a execução do programa
	carregado na memória de instruções
*/
void UC_run();

#endif