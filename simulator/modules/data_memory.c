#include "data_memory.h"

DM dm;

void W_DM(char value) {
	int index = binaryToDecimal(dm.address, 1);
	if(index < 0 || index > DM_SIZE) return; //Desconsidera quando o valor na entrada do endereço é inválido
								//mandado as vezes quando não se deseja fazer uma operação nem de leitura nem escrita
	
	if(value == '1') { //Escrita
		//Copia para a posição (dm.address) do vetor 'dm.data', o valor da entrada 'dm.input'
		strcpy(dm.data[index], dm.input);
		strcpy(dm.output, ZERO); //zera a saída
	} else if(value == '0') { //Leitura
		//Copia para a saída 'dm.output' o valor presente no vetor 'dm.data', na posição (dm.address)
		strcpy(dm.output, dm.data[index]);
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