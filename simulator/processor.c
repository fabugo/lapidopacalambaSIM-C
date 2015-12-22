#include <stdio.h>

#include "modules/program_counter.h"
#include "modules/memory_instruction.h"
#include "modules/register_bank.h"
#include "modules/data_memory.h"
#include "modules/alu.h"
#include "modules/register_flags.h"
#include "modules/signal_extender.h"
#include "modules/tester_flags.h"

//#include "modules/unit_control.h"

#include "defs.h"
#include "../lib/string.h"
#include <string.h>

int main(int argc, char *argv[]) {
	PC_start();
	MI_start();
	SE_start();
	RB_start();
	DM_start();
	
	ALU_start();
	RF_start();
	TF_start();
}