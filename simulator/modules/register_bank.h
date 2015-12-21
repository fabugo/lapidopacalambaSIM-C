#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

struct REGISTER_BANK {
    int a;
};
typedef struct REGISTER_BANK RB;

extern RB register_bank;

char *readA();
char *readB();
int writec();
int setA();
int setB();
int setC();

#endif