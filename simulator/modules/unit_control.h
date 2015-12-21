#ifndef UNIT_CONTROL_H
#define UNIT_CONTROL_H

struct UNIT_CONTROL {
    char[9] TYPE_OP;
    char[6] OP_ALU;
    char[3] OP_SE;
    char[4] OP_TF;
    int W_CP;
    int W_RB;
    int W_DM;
    int W_RF;
    int S_MXSE;
    int S_MXRB;
};
typedef struct UNIT_CONTROL UC;

extern UC uc;

#endif