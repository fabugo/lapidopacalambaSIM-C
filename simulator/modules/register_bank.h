#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include <string.h>
#include "../defs.h"
#include "../../lib/string.h"

#include "memory_instruction.h"

struct REGISTER_BANK {
    char *input_RA;
    char *input_RB;
    char *input_WC;
    char *input_WPC;

    char output_PRA[33];
    char output_PRB[33];

    char registers[RB_SIZE][33];
};
typedef struct REGISTER_BANK R_BANK;

extern R_BANK rbank;

void RB_start();

void W_RB(int value);

void RST_RB(int value);

#endif