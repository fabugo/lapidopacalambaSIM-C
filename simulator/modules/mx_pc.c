#include "mx_pc.h"

MX_PC mx_pc;

void S_MXPC(char value) {
	if(value == '0') {
		//Seleciona a entrada 'mx_pc.input_ALU' para a saída 'mx_pc.output'
		strcpy(mx_pc.output, mx_pc.input_ALU);
	} else if(value == '1') {
		//Seleciona a entrada 'mx_pc.input_ADD'  para a saída 'mx_pc.output'
        strcpy(mx_pc.output, mx_pc.input_ADD);
    }
}