#ifndef ALU_H
#define ALU_H

#include <stdlib.h>
#include <string.h>

#include "../defs.h"
#include "register_bank.h"

struct ALU {
    char *input_A;
    char *input_B;

    char result[33];
    int flags[4]; //O, S, C, Z
};
typedef struct ALU ALU;

extern ALU alu;

void ALU_start();
void OP_ALU(char *operation);

#endif