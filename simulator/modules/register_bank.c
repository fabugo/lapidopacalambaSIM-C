#include "register_bank.h"

R_BANK rbank;

void RB_start() {
	rbank.input_RA = (char*) mi.output;
    rbank.input_RB = (char*) mi.output;
    rbank.input_WC = (char*) mi.output;
    rbank.input_WPC = (char*) mi.output;
}

void W_RB(int value){	
	if(value) {
		strcpy(rbank.registers[binaryToDecimal(substring(rbank.input_WC, 0, 4), 0)], rbank.input_WPC);
	} else {
		strcpy(rbank.output_PRA, rbank.registers[binaryToDecimal(substring(rbank.input_RA, 0, 4), 0)]);
		strcpy(rbank.output_PRA, rbank.registers[binaryToDecimal(substring(rbank.input_RB, 0, 4), 0)]);
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