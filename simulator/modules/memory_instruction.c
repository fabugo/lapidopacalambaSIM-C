#include "memory_instruction.h"

MI mi;

void W_MI(char value) {
	int index = binaryToDecimal(mi.input, 1);
	if(index < 0 || index > MI_SIZE) return;//Desconsidera quando o valor na entrada do endereço é inválido
								//mandado as vezes quando não se deseja fazer uma operação nem de leitura nem escrita

	if(value == '1') {
		//Carrega na saída 'mi.output', o valor presente na posição (mi.input) do vetor 'mi.instruction'
		strcpy(mi.output, mi.instruction[index]);
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