#include "program_counter.h"

PC pc;

void PC_start() {
	strcpy(pc.output, ZERO);

	RST_PC(1);
}

void W_PC(int value) {
	if(value) {
		strcpy(pc.output, pc.input);
	}
}

void RST_PC(int value) {
	if(value) {
		strcpy(pc.output, ZERO);
	}
}