#include "data_memory.h"

DM dm;

void DM_start() {
	dm.input = (char*) &rbank.output_PRA;
	dm.address = (char*) &rbank.output_PRB;
}

void W_DM(int value) {
	if(value) {
		strcpy(dm.data[binaryToDecimal(dm.address, 0)], dm.input);
		strcpy(dm.output, ZERO);
	} else {
		strcpy(dm.output, dm.data[binaryToDecimal(dm.address, 0)]);
	}
}

void RST_DM(int value) {
	if(value) {
		strcpy(dm.output, ZERO);

		int x;
		for(x = 0; x < DM_SIZE; x++) {
			strcpy(dm.data[x], ZERO);
		}
	}
}