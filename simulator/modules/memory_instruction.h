#ifndef MEMORY_INSTRUCTION_H
#define MEMORY_INSTRUCTION_H

#include <string.h>
#include "../defs.h"
#include "../../lib/string.h"

#include "program_counter.h"

struct MEMORY_INSTRUCTION {
	char *input;
	char output[33];
    char instruction[MI_SIZE][33];
};
typedef struct MEMORY_INSTRUCTION MI;

extern MI mi;

void MI_start();

void W_MI(int value);

void RST_MI(int value);

#endif