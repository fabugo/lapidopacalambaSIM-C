#include "register_bank.h"

R_BANK rbank;

void W_RB(char value){	
	if(value == '1') { //Escrita
		//Copia para a posição (rbank.input_WC) do vetor 'rbank.registers', o valor da entrada 'rbank.input_WPC)'
		strcpy(rbank.registers[binaryToDecimal(substring(rbank.input_WC, 8, 11), 0)], rbank.input_WPC);
	} else if(value == '0') { //Leitura
		//Copia para a saída 'rbank.output_PRA' o valor presente no vetor 'rbank.registers', na posição (rbank.input_RA)
		strcpy(rbank.output_PRA, rbank.registers[binaryToDecimal(substring(rbank.input_RA, 12, 15), 0)]);//bits 19:16
		//Copia para a saída 'rbank.output_PRB' o valor presente no vetor 'rbank.registers', na posição (rbank.input_RB)
		strcpy(rbank.output_PRB, rbank.registers[binaryToDecimal(substring(rbank.input_RB, 16, 19), 0)]);//bits 15:12
	}
}

void RST_RB(char value){
	if(value == '1') {
		strcpy(rbank.output_PRA, ZERO); //Zera a saída 'rbank.output_PRA'
		strcpy(rbank.output_PRB, ZERO); //Zera a saída 'rbank.output_PRB'

		int x;
		for(x = 0; x < RB_SIZE; x++) { //Zera todos os registradores
			strcpy(rbank.registers[x], ZERO);
		}
	}
}