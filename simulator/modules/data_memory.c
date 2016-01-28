#include "data_memory.h"

DM dm;

void W_DM(char value) {
	if(value == '1') { //Escrita
		//Copia para a posição (dm.address) do vetor 'dm.data', o valor da entrada 'dm.input'
		strcpy(dm.data[binaryToDecimal(dm.address, 0)], dm.input);
		strcpy(dm.output, ZERO); //zera a saída
	} else if(value == '0') { //Leitura
		//Copia para a saída 'dm.output' o valor presente no vetor 'dm.data', na posição (dm.address)
		strcpy(dm.output, dm.data[binaryToDecimal(dm.address, 0)]);
	}
}

void RST_DM(char value) {
	if(value == '1') {
		strcpy(dm.output, ZERO); //Zera a saída 'dm.output'

		int x;
		for(x = 0; x < DM_SIZE; x++) { //Zera toda a memória de dados
			strcpy(dm.data[x], ZERO);
		}
	}
}