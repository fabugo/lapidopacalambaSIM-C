/*
	Arquivo que inicializa o simulador, carrega as instruções e inicia a execução do programa
*/
#include <stdio.h>
#include <string.h>

#include "defs.h"
#include "reader.h"
#include "../lib/string.h"
#include "modules/program_counter.h"
#include "modules/memory_instruction.h"
#include "modules/register_bank.h"
#include "modules/data_memory.h"
#include "modules/alu.h"
#include "modules/register_flags.h"
#include "modules/signal_extender.h"
#include "modules/tester_flags.h"
//#include "modules/unit_control.h"

int main(int argc, char *argv[]) {
	/********Inicializa os componentes do processador*********/
	PC_start();
	MI_start();
	SE_start();
	RB_start();
	DM_start();
	ALU_start();
	RF_start();
	TF_start();
	UC_start();
	/*********************************************************/

	/******Carrega as instruções na memória de instrução******/
	Instr *instr = read("input"); //Lê o arquivo de entrada
	int x;
	for(x = 0; x < MI_SIZE && instr != NULL; x++) {
	//Percorre instrução a instrução copiando-as para a memória
		strcpy(mi.instruction[x], instr->content);
		instr = instr->next;
	}
	/*********************************************************/

	char result;
	result = 'a' & '1';
	printf("%c", result);

	UC_run();
}