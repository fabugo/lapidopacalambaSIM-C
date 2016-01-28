#include "mx_pc.h"
MX_PC mx_pc;
void PC_start() {
	strcpy(mx_pc.output, ZERO);
}
void W_PC(int value) {
	if(value) {
		strcpy(pc.output, pc.input_ULA);
	}else{
        strcpy(pc.output, pc.input_PC);
    }
}
