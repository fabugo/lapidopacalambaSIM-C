#include "register_bank.h"

R_BANK rbank;

void RB_start() {
	rbank.input_RA = (char*) mi.output;
    rbank.input_RB = (char*) mi.output;
    rbank.input_WC = (char*) mi.output;
    rbank.input_WPC = (char*) mi.output;
}

void W_RB(int value){	
	/*if(value) {
		rbank.registers[rbank.input_WC] = input_WPC;
	} else {
		rbank.output_PRA = rbank.registers[rbank.input_RA];
		rbank.output_PRB = rbank.registers[rbank.input_RB];
	}*/
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