#include "program_counter.h"

PC pc;

void W_PC(char value) {
	if(value == '1') {
		//Copia para a saída 'pc.output' o valor da entrada 'pc.input'
		strcpy(pc.output, pc.input);
	}
}

void RST_PC(char value) {
	if(value == '1') {
		//Zera a saída 'pc.output'
		strcpy(pc.output, ZERO);
	}
}