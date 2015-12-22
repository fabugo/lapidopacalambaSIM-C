#include "register_bank.h"

R_BANK rbank;

void RB_start() {
	rbank.input_RA = (char*) mi.output;
    rbank.input_RB = (char*) mi.output;
    rbank.input_WC = (char*) mi.output;
    rbank.input_WPC = (char*) mi.output;

    RST_RB(1);
}

void W_RB(int value){	
	if(value) {
		strcpy(rbank.registers[binaryToDecimal(substring(rbank.input_WC, 8, 11), 0)], rbank.input_WPC);//bits 23:20
	} else {
		strcpy(rbank.output_PRA, rbank.registers[binaryToDecimal(substring(rbank.input_RA, 12, 15), 0)]);//bits 19:16
		strcpy(rbank.output_PRA, rbank.registers[binaryToDecimal(substring(rbank.input_RB, 16, 19), 0)]);//bits 15:12
	}
}

void RST_RB(int value){
	if(value) {
		strcpy(rbank.output_PRA, ZERO);
		strcpy(rbank.output_PRB, ZERO);

		int x;
		for(x = 0; x < RB_SIZE; x++) {
			strcpy(rbank.registers[x], ZERO);
		}
	}
}