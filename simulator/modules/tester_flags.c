#include "tester_flags.h"

TF tf;

void TF_start() {
	tf.input_flags = (int*) &rf.output_flags;
	tf.cond = (char*) &mi.output;

	tf.output = 0;
}

void OP_TF(char *value) {
	char *cond = substring(tf.cond, 17, 19); //bits 14:12

	if(strEquals(value, "111")) {
		tf.output = 1;
	} else if(!startWith(value, "00")) {
		tf.output = 0;
	} else { //Começa com 00
		int jType = (value[2] == '0')
			? 0  //jf
			: 1; //jt
		if(strEquals(cond, "000")) //true
			tf.output =  jType;
		else if(strEquals(cond, "001")) //neg = flag S
			tf.output = (jType)
					? tf.input_flags[1]
					: !tf.input_flags[1];
		else if(strEquals(cond, "010")) //zero = flag Z
			tf.output = (jType)
					? tf.input_flags[3]
					: !tf.input_flags[3];
		else if(strEquals(cond, "100")) //carry = flag C
			tf.output = (jType)
					? tf.input_flags[2]
					: !tf.input_flags[2];
		else if(strEquals(cond, "101")) //negzero = flag S e Z
			tf.output = (jType)
					? (tf.input_flags[1] && tf.input_flags[3])
					: !(tf.input_flags[1] && tf.input_flags[3]);
		else if(strEquals(cond, "111")) //overflow = flag O
			tf.output = (jType)
					? tf.input_flags[0]
					: !tf.input_flags[0];
	}
}
