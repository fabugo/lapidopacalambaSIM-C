#ifndef MX_SE_H
#define MX_SE_H
#include <string.h>
#include "../defs.h"
struct MX_SE {
    char input_RB[33];
    char input_SE[33];
    char output[33];
};
typedef struct MX_SE MX_SE;
extern MX_SE mx_se;
void MX_PC_start();
void SET(int value);
#endif
