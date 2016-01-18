#ifndef ALU_H
#define ALU_H

struct ALU {
    char *input_A;
    char *input_B;

    char result[33];
    int flags[4];
};
typedef struct ALU ALU;

extern ALU alu;

void ALU_start();
void OP_ALU(int value);
#endif
