#ifndef DATA_MEMORY_H
#define DATA_MEMORY_H

#include <string.h>
#include "../defs.h"
#include "../../lib/string.h"

#include "register_bank.h"

struct DATA_MEMORY {
    char *input;
    char *address;
    char output[33];
    char data[DM_SIZE][33];
};
typedef struct DATA_MEMORY DM;

extern DM dm;

void DM_start();

void W_DM(int value);

void RST_DM(int value);

#endif