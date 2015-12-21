#include "register_flags.h"

RF rf;

void RF_start(){
	rf.input_flags = (int*) &alu.flags;
}

void W_RF(int value) {
	switch(value) {
		case 0: //W_RF = 000
		break;
		case 1: //W_RF = 001
			rf.output_flags[3] = rf.input_flags[3];
		break;
		case 2: //W_RF = 010
			rf.output_flags[1] = rf.input_flags[1];
			rf.output_flags[3] = rf.input_flags[3];
		break;
		case 3: //W_RF = 011
			rf.output_flags[1] = rf.input_flags[1];
			rf.output_flags[2] = rf.input_flags[2];
			rf.output_flags[3] = rf.input_flags[3];
		break;
		case 4: //W_RF = 100
			rf.output_flags[0] = rf.input_flags[0];
			rf.output_flags[1] = rf.input_flags[1];
			rf.output_flags[2] = rf.input_flags[2];
			rf.output_flags[3] = rf.input_flags[3];
		break;
	}
}

void RST_RF(int value) {
	if(value) {
		rf.output_flags[0] = 0;
		rf.output_flags[1] = 0;
		rf.output_flags[2] = 0;
		rf.output_flags[3] = 0;
	}
}