#include "signal_extender.h"

SE se;

void OP_SE(char value) {
	if(value == '1') {
		//preenche os 16 bits menos significativos da saída do mi com o bit mais significativo.
		//Exemplo, se for o valor 1001110011101100, a saída será 11111111111111111001110011101100
		if(se.input[16] == '1') {
			sprintf(se.output, "%s%s", "1111111111111111", substring(se.input, 16, 31));
		} else {
			sprintf(se.output, "%s%s", "0000000000000000", substring(se.input, 16, 31));
		}
	} else if(value == '0') {
		//Idem, com os 12 bits menos significativos
		if(se.input[20] == '1') {
			sprintf(se.output, "%s%s", "11111111111111111111", substring(se.input, 20, 31));
		} else {
			sprintf(se.output, "%s%s", "00000000000000000000", substring(se.input, 20, 31));
		}
	}
}

void RST_SE(char value) {
	if(value == '1') { //Zera a saída 'se.output'
		strcpy(se.output, ZERO);
	}
}