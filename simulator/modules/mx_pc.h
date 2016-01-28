#ifndef MX_PC_H
#define MX_PC_H
#include <string.h>
#include "../defs.h"
struct MX_PC {
    char input_ULA[33];
    char input_PC[33];
    char output[33];
};
typedef struct MX_PC MX_PC;
extern MX_PC MX_PC;
void MX_PC_start();
void SET(int value);
#endif
