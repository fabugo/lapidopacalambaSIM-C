#include "register_flags.h"

RF rf;

void W_RF(int value) {
	switch(value) {
		RF_loadFlags();

		case 0: //W_RF = 000
		break;
		case 1: //W_RF = 001
			rf.out_flags[3] = in_flags[3];
		break;
		case 2: //W_RF = 010
			rf.out_flags[1] = in_flags[1];
			rf.out_flags[3] = in_flags[3];
		break;
		case 3: //W_RF = 011
			rf.out_flags[1] = in_flags[1];
			rf.out_flags[2] = in_flags[2];
			rf.out_flags[3] = in_flags[3];
		break;
		case 4: //W_RF = 100
			rf.out_flags[0] = in_flags[0];
			rf.out_flags[1] = in_flags[1];
			rf.out_flags[2] = in_flags[2];
			rf.out_flags[3] = in_flags[3];
		break;
	}
}

void RST_RF(int value) {
	if(value) {
		rf.out_flags[0] = 0;
		rf.out_flags[1] = 0;
		rf.out_flags[2] = 0;
		rf.out_flags[3] = 0;
	}
}

void RF_load() {
	in_flags[0] = ula.flags[0];
	in_flags[1] = ula.flags[1];
	in_flags[2] = ula.flags[2];
	in_flags[3] = ula.flags[3];
}