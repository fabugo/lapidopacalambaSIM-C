#ifndef REGISTER_FLAGS_H
#define REGISTER_FLAGS_H

#include "alu.h"

struct REGISTER_FLAGS {
	int *input_flags; //O, S, C, Z
    int output_flags[4]; //O, S, C, Z
};
typedef struct REGISTER_FLAGS RF;

extern RF rf;

void RF_start();

void W_RF(int value);

void RST_RF(int value);

#endif