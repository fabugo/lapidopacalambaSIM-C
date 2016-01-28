#include "mx_rb.h"
MX_RB mx_rb;
void MX_RB_start() {
	strcpy(mx_se.output, ZERO);
}
void SET(int value) {
	if(value) {
		strcpy(mx_rb.output, mx_rb.input_ALU);
	}else if (value == 2){
        strcpy(mx_rb.output, mx_rb.input_MEM);
    }else{
        strcpy(mx_rb.output, mx_rb.input_PC);
    }
}
