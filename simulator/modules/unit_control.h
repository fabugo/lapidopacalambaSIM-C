#ifndef UNIT_CONTROL_H
#define UNIT_CONTROL_H

#include "../defs.h"
#include "../../lib/string.h"

#include "memory_instruction.h"
#include "program_counter.h"
#include "data_memory.h"
#include "register_bank.h"
#include "register_flags.h"
#include "signal_extender.h"
#include "tester_flags.h"

struct UNIT_CONTROL {
    char *TYPE_OP;
    char[6] OP_ALU;
    char[3] OP_SE;
    char[4] OP_TF;
    int W_PC;
    int W_RB;
    int W_DM;
    int W_RF;
    int W_MI;
};
typedef struct UNIT_CONTROL UC;

extern UC uc;

void UC_run();
void UC_start();
void IF();
void ID();
void EX();
void WB();

#endif
