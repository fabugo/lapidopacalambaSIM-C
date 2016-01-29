#include "mx_rb.h"

MX_RB mx_rb;

void S_MXRB(char *value) {
	if(strEquals(value, "00")) {
		//Seleciona a entrada 'mx_rb.input_PC' para a saída 'mx_se.output'
        strcpy(mx_rb.output, mx_rb.input_PC);
	} else if(strEquals(value, "01")) {
		//Seleciona a entrada 'mx_rb.input_DM' para a saída 'mx_se.output'
        strcpy(mx_rb.output, mx_rb.input_DM);
    } else if(strEquals(value, "10")) {
    	//Seleciona a entrada 'mx_rb.input_ALU' para a saída 'mx_se.output'
		strcpy(mx_rb.output, mx_rb.input_ALU);
    }
}