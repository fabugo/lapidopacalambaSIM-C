#include <stdio.h>
#include <string.h>

struct {
    signed char  r0[32];
    signed char  r1[32];
    signed char  r2[32];
    signed char  r3[32];
    signed char  r4[32];
    signed char  r5[32];
    signed char  r6[32];
    signed char  r7[32];
    signed char  r8[32];
    signed char  r9[32];
    signed char  r10[32];
    signed char  r11[32];
    signed char  r12[32];
    signed char  r13[32];
    signed char  r14[32];
    signed char  r15[32];
} RB;

int main(int argc,char const *argv[]) {

    RB.r1 = "00000000000000000000000000000001";
    RB.r1 = "00000000000000000000000000000010";

    signed char byte1;

    FILE *file;
    file = fopen("program", "r");

    if(!strcmp(op5,"0001")){

    }

    fclose(file);
}
