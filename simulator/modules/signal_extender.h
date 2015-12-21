#ifndef SIGNAL_EXTENDER_H
#define SIGNAL_EXTENDER_H

#include <stdio.h>
#include "../defs.h"
#include "../../lib/string.h"

#include "memory_instruction.h"

struct SIGNAL_EXTENDER {
    char *input;
    char output[33];
};
typedef struct SIGNAL_EXTENDER SE;

extern SE se;

void SE_start();

void OP_SE(int value);

#endif