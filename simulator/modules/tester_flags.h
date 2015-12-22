#ifndef TESTER_FLAGS_H
#define TESTER_FLAGS_H

#include "../../lib/string.h"

#include "register_flags.h"
#include "memory_instruction.h"

struct TESTER_FLAGS {
	int *input_flags; //O, S, C, Z
    char *cond;
    int output;
};
typedef struct TESTER_FLAGS TF;

extern TF tf;

void TF_start();

void OP_TF(int value);

#endif