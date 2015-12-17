#include <stdio.h>
#include <string.h>

#include "reader.h"

#define	INSTRUCTION_SIZE	33  //32 + 1 para o \0

struct {
    signed char r0[INSTRUCTION_SIZE];
    signed char r1[INSTRUCTION_SIZE];
    signed char r2[INSTRUCTION_SIZE];
    signed char r3[INSTRUCTION_SIZE];
    signed char r4[INSTRUCTION_SIZE];
    signed char r5[INSTRUCTION_SIZE];
    signed char r6[INSTRUCTION_SIZE];
    signed char r7[INSTRUCTION_SIZE];
    signed char r8[INSTRUCTION_SIZE];
    signed char r9[INSTRUCTION_SIZE];
    signed char r10[INSTRUCTION_SIZE];
    signed char r11[INSTRUCTION_SIZE];
    signed char r12[INSTRUCTION_SIZE];
    signed char r13[INSTRUCTION_SIZE];
    signed char r14[INSTRUCTION_SIZE];
    signed char r15[INSTRUCTION_SIZE];
} RB;

int main(int argc, char const *argv[]) {
    Instr *pc = read("input");

    while(pc != NULL) {
        printf("%4.d  -  %s\n", pc->address, pc->content);
        pc = pc->next;
    }
}
