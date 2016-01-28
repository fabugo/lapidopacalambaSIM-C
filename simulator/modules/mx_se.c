#include "mx_se.h"

MX_SE mx_se;

void MX_SE_SET(char value) {
	if(value == '0') {
		//Seleciona a entrada 'mx_se.input_RB' para a saída 'mx_se.output'
		strcpy(mx_se.output, mx_se.input_RB);
	} else if(value == '1') {
		//Seleciona a entrada 'mx_se.input_SE' para a saída 'mx_se.output'
        strcpy(mx_se.output, mx_se.input_SE);
    }
}