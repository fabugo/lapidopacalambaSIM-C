#ifndef ALU_H
#define ALU_H

struct ALU {
	int operation;
    char input_A[33];
    char input_B[33];
    char output[33];
    int flags[4];
};
typedef struct ALU ALU;

extern ALU alu;

void ALU_start();
void OP_ALU(int value);
#endif
