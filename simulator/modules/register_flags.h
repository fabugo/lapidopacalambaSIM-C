#ifndef REGISTER_FLAGS_H
#define REGISTER_FLAGS_H

struct REGISTER_FLAGS {
	int in_flags[4]; //O, S, C, Z
    int out_flags[4]; //O, S, C, Z
};
typedef struct REGISTER_FLAGS RF;

extern RF rf;

void W_RF(int value);

void RST_RF(int value);

#endif