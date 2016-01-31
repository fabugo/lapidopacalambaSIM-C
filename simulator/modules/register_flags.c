#include "register_flags.h"

RF rf;

void W_RF(char *value) {
	if(strEquals(value, "000")) {				//Não atualiza nenhuma flag
	} else if(strEquals(value, "001")) {		//Atualiza a flag Z
		rf.output_OSCZ[3] = rf.input_OSCZ[3];
	} else if(strEquals(value, "010")) {		//Atualiza as flags S e Z
		rf.output_OSCZ[1] = rf.input_OSCZ[1];
		rf.output_OSCZ[3] = rf.input_OSCZ[3];
	} else if(strEquals(value, "011")) {		//Atualiza as flags S, C e Z
		rf.output_OSCZ[1] = rf.input_OSCZ[1];
		rf.output_OSCZ[2] = rf.input_OSCZ[2];
		rf.output_OSCZ[3] = rf.input_OSCZ[3];
	} else if(strEquals(value, "100")) {		//Atualiza as flags O, S, C e Z
		rf.output_OSCZ[0] = rf.input_OSCZ[0];
		rf.output_OSCZ[1] = rf.input_OSCZ[1];
		rf.output_OSCZ[2] = rf.input_OSCZ[2];
		rf.output_OSCZ[3] = rf.input_OSCZ[3];
	}
}

void RST_RF(char value) {
	if(value == '1') { //Zera todas as flags
		rf.output_OSCZ[0] = '0';
		rf.output_OSCZ[1] = '0';
		rf.output_OSCZ[2] = '0';
		rf.output_OSCZ[3] = '0';
	}
}