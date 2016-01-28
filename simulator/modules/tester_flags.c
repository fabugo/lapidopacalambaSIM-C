#include "tester_flags.h"

TF tf;

void OP_TF(char *value) {
	char *cond = substring(tf.cond, 17, 19); //bits 14:12

	if(strEquals(value, "111")) {
	//Não jumper, seleciona a entrada do contador de programa no multiplexador mx_pc
		tf.output = 1;
	} else if(!startWith(value, "00")) {
	//Jumper incondicional, seleciona a entrada da unidade lógica aritmética no multiplexador mx_pc
		tf.output = 0;
	} else { 							
	//Começa com 00, jumper condicional. Verifica o tipo (jf ou jt) e a condição
		int jType = (value[2] == '0')
			? 0  //jf
			: 1; //jt
		if(strEquals(cond, "000")) 			//Condição true
			tf.output =  jType;
		else if(strEquals(cond, "001")) 	//Condição neg = flag S
			tf.output = (jType)
					? tf.input_flags[1]
					: !tf.input_flags[1];
		else if(strEquals(cond, "010")) 	//Condição zero = flag Z
			tf.output = (jType)
					? tf.input_flags[3]
					: !tf.input_flags[3];
		else if(strEquals(cond, "100")) 	//Condição carry = flag C
			tf.output = (jType)
					? tf.input_flags[2]
					: !tf.input_flags[2];
		else if(strEquals(cond, "101")) 	//Condição negzero = flag S e Z
			tf.output = (jType)
					? (tf.input_flags[1] && tf.input_flags[3])
					: !(tf.input_flags[1] && tf.input_flags[3]);
		else if(strEquals(cond, "111")) 	//Condição overflow = flag O
			tf.output = (jType)
					? tf.input_flags[0]
					: !tf.input_flags[0];
	}
}

void RST_TF(char value) {
	if(value == '1') { //Zera a saída 'tf.output'
		tf.output = '0';
	}
}