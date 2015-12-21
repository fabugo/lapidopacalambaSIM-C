#ifndef ALU_H
#define ALU_H

struct ALU {
	char[6] operation;
    char[33] input_A;
    char[33] input_B;
    char[33] output;

    int[4] flags;
};
typedef struct ALU ALU;

extern ALU alu;

#endif