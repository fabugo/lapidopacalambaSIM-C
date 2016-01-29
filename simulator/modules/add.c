#include "add.h"

ADD add;

void addi();

/*
	Função que incrementa 1 no valor de 'add.input' e o carrega na
	saída 'add.output'
*/
void ADD_PC(char value) {
	if(value == '1') {
		addi();
	}
}

void addi() {
	char *one = "00000000000000000000000000000001";
    char carryIn = '0', carryOut = '0';

    int i = 31;
    for(i;i>=0;i--) {
        add.output[i] = fullAdder(carryIn, add.input[i], one[i], &carryOut);
        carryIn = carryOut;
    }
    add.output[32] = '\0';
}