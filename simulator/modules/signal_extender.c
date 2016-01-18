#include "signal_extender.h"

SE se;

void SE_start() {
	se.input = (char*) &mi.output;
	
	strcpy(se.output, ZERO);
}

void OP_SE(int value) {
	if(value) {
		//preenche os 16 bits menos significativos da saída do mi com 0. Se eles forem
		//o valor 0001110011101100, a saída sera 00000000000000000001110011101100
		sprintf(se.output, "%s%s", "0000000000000000", substring(se.input, 16, 31));
	} else {
		//Idem, com os 12 bits menos significativos
		sprintf(se.output, "%s%s", "00000000000000000000", substring(se.input, 20, 31));
	}
}