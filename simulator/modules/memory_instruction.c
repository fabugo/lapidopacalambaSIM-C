#include "memory_instruction.h"

MI mi;

void W_MI(char value) {
	if(value == '1') {
		//Carrega na saída 'mi.output', o valor presente na posição (mi.input) do vetor 'mi.instruction'
		strcpy(mi.output, mi.instruction[binaryToDecimal(mi.input, 0)]);
	}
}

void RST_MI(char value) {
	if(value == '1') {
		strcpy(mi.output, ZERO); //Zera a saída 'mi.output'

		int x;
		for(x = 0; x < MI_SIZE; x++) { //Zera toda a memória de instruções
			strcpy(mi.instruction[x], ZERO);
		}
	}
}