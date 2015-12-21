#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include <string.h>
#include "../defs.h"

struct PROGRAM_COUNTER {
    char input[33];
    char output[33];
};
typedef struct PROGRAM_COUNTER PC;

extern PC pc;

void PC_start();

void W_PC(int value);

void RST_PC(int value);

#endif