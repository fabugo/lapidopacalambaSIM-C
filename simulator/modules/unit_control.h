#ifndef UNIT_CONTROL_H
#define UNIT_CONTROL_H

#include <stdlib.h>
#include <stdio.h>

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
    char OP_ALU[6];
    char OP_SE[3];
    char OP_TF[4];
    int W_PC;
    int W_RB;
    int W_DM;
    int W_RF;
    int W_MI;
};
typedef struct UNIT_CONTROL UC;

extern UC uc;

void UC_start();
void UC_run();
void IF();
void ID();
void EX();
void WB();

#endif