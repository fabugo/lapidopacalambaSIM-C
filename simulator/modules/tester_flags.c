#include "tester_flags.h"

TF tf;

void TF_start() {
	tf.input_flags = rf.output_flags;
	tf.cond = (char*) &mi.output;

	tf.output = 0;
}

void OP_TF(int value) {
	//value - jt ou jf
	char *flags = substring(tf.cond, 0, 2);
	if(strEquals(flags, "001")) //neg = flag S
		tf.output = (value)
				? tf.input_flags[1]
				: !tf.input_flags[1];
	else if(strEquals(flags, "010")) //zero = flag Z
		tf.output = (value)
				? tf.input_flags[3]
				: !tf.input_flags[3];
	else if(strEquals(flags, "100")) //carry = flag C
		tf.output = (value)
				? tf.input_flags[2]
				: !tf.input_flags[2];
	else if(strEquals(flags, "101")) //negzero = flag S e Z
		tf.output = (value)
				? (tf.input_flags[1] && tf.input_flags[3])
				: !(tf.input_flags[1] && tf.input_flags[3]);
	else if(strEquals(flags, "110")) //true
		tf.output =  value;
	else if(strEquals(flags, "111")) //overflow = flag O
		tf.output = (value)
				? tf.input_flags[0]
				: !tf.input_flags[0];
}