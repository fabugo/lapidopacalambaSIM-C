#ifndef TESTER_FLAGS_H
#define TESTER_FLAGS_H

struct TESTER_FLAGS {
    int OP_TF;
    int overflow;
    int signal;
    int carry;
    int zero;
    char cond[5];
    int S_MXPC;
};
typedef struct TESTER_FLAGS TF;

extern TF tf;

#endif