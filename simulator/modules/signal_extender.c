#include "signal_extender.h"

SE se;

void SE_start() {
	se.input = (char*) &mi.output;
	
	strcpy(se.output, ZERO);
}

void OP_SE(int value) {
	if(value) {
		sprintf(se.output, "%s%s", "0000000000000000", substring(se.input, 16, 31));
	} else {
		sprintf(se.output, "%s%s", "00000000000000000000", substring(se.input, 20, 31));
	}
}