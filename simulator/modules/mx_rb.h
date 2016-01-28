#ifndef MX_RB_H
#define MX_RB_H
#include <string.h>
#include "../defs.h"
struct MX_RB {
    char input_ALU[33];
    char input_MEM[33];
    char input_PC[33];
    char output[33];
};
typedef struct MX_RB MX_RB;
extern MX_RB mx_rb;
void MX_RB_start();
void SET(int value);
#endif
