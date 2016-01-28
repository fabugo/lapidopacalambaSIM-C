#include "mx_pc.h"
MX_PC mx_pc;
void MX_PC_start() {
	strcpy(mx_pc.output, ZERO);
}
void SET(int value) {
	if(value) {
		strcpy(mx_pc.output, mx_pc.input_ULA);
	}else{
        strcpy(mx_pc.output, mx_pc.input_PC);
    }
}
