#include <stdio.h>

//#include "modules/alu.h"
#include "modules/data_memory.h"
#include "modules/memory_instruction.h"
#include "modules/program_counter.h"
#include "modules/register_bank.h"
//#include "modules/signal_extender.h"
//#include "modules/register_flags.h"
//#include "modules/tester_flags.h"
//#include "modules/unit_control.h"

#include "defs.h"
#include "../lib/string.h"
#include <math.h>

int main(int argc, char *argv[]) {
	//printf(">%lld<\n", binaryToDecimal("1000", 0));

	PC_start();
	MI_start();
	RB_start();
	DM_start();

	printf(">%s<\n", pc.output);
	printf(">%s<\n", mi.input);
}