#include "tester_flags.h"

TF tf;

void OP_TF(char *value) {
	char *cond = substring(tf.cond, 17, 19); //bits 14:12

	if(strEquals(value, "111")) {
	//Não jumper, seleciona a entrada do contador de programa no multiplexador mx_pc
		tf.output = '1';
	} else if(!startWith(value, "00")) {
	//Jumper incondicional, seleciona a entrada da unidade lógica aritmética no multiplexador mx_pc
		tf.output = '0';
	} else { 							
	//Começa com 00, jumper condicional. Verifica o tipo (jf ou jt) e a condição
		char jType = value[2]; //0 - jf, 1 - tf
		if(strEquals(cond, "000")) 			//Condição true
			tf.output =  '1';
		else if(strEquals(cond, "001")) 	//Condição neg = flag S
			tf.output = tf.input_OSCZ[1];
		else if(strEquals(cond, "010")) 	//Condição zero = flag Z
			tf.output = tf.input_OSCZ[3];
		else if(strEquals(cond, "100")) 	//Condição carry = flag C
			tf.output = tf.input_OSCZ[2];
		else if(strEquals(cond, "101")) 	//Condição negzero = flag S e Z
			tf.output = !(tf.input_OSCZ[1] == tf.input_OSCZ[3] && tf.input_OSCZ[1] == '0') ? '1' : '0';
		else if(strEquals(cond, "111")) 	//Condição overflow = flag O
			tf.output = tf.input_OSCZ[0];
		
		//Caso seja jt, inverte o sinal para o MX_PC selecione a saída da ula, caso verdadeiro.
		if(jType == '1')
			tf.output = (tf.output == '1') ? '0' : '1';
	}
}

void RST_TF(char value) {
	if(value == '1') { //Zera a saída 'tf.output'
		tf.output = '0';
	}
}