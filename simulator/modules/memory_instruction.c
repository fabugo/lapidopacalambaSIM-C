#include "memory_instruction.h"

MI mi;

void MI_start() {
	mi.input = (char*) &pc.output;

	RST_MI(1);
}

void W_MI(int value) {
	if(value) {
		strcpy(mi.output, mi.instruction[binaryToDecimal(mi.input, 0)]);
	}
}

void RST_MI(int value) {
	if(value) {
		strcpy(mi.output, ZERO);

		int x;
		for(x = 0; x < MI_SIZE; x++) {
			strcpy(mi.instruction[x], ZERO);
		}
	}
}