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
	PC_start();
	MI_start();
	SE_start();
	RB_start();
	DM_start();
	
	ALU_start();
	RF_start();
	TF_start();

	//Carrega as instruções na memória de instrução
	Instr *instr = read("input");
	int x;
	for(x = 0; x < MI_SIZE && instr != NULL; x++) {
		strcpy(mi.instruction[x], instr->content);
		instr = instr->next;
	}
}