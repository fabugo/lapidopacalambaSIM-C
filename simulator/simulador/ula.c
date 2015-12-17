void execALU(){
	switch(controlUla){
		case  1: add();      break;
		case  2: addinc();   break;
		case  3: inca();     break;
		case  4: subdec();   break;
		case  5: sub();      break;
		case  6: deca();     break;
		case  7: lsl();      break;
		case  8: asr();      break;
		case  9: zeros();    break;
		case 10: and(); 	 break;
		case 11: andnota();	 break;
		case 12: passb(); 	 break;
		case 13: andnotb();  break;
		case 14: passa(); 	 break;
		case 15: xor();      break;
		case 16: or();	     break;
		case 17: nand();	 break;
		case 18: xnor();	 break;
		case 19: passnota(); break;
		case 20: ornota();	 break;
		case 21: passnotb(); break;
		case 22: ornotb();	 break;
		case 23: nor();		 break;
		case 24: ones();	 break;
	}
}

void add(){
	ULAOut = A + B; // dados vindos do banco de registradores
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = ?
	flags.carry = ?
}

void addinc(){
	ULAOut = A + B + 1;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = ?
	flags.carry = ?
}

void inca(){
	ULAOut = A + 1;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = ?;
	flags.carry = ?
}

void subdec(){
	ULAOut = A - B - 1;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = ?
	flags.carry = ?
}

void sub(){
	ULAOut = A - B;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = ?
	flags.carry = ?
}

void deca(){
	ULAOut = A - 1;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = ?
	flags.carry = ?
}

void lsl(){
	ULAOut = A << 1;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = ?
}

void asr(){
	ULAOut = A >> 1;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void zeros(){
	ULAOut = 0;
	flags.zero = TRUE;
	alu_flags.neg = FALSE;
	alu_flags.negzero = TRUE;
	alu_flags.overflow = FALSE;
	alu_flags.carry = FALSE;
}

void and(){
	ULAOut = A & B;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;

}

void andnota(){
	ULAOut = (~A) & B;
	flags.zero = ULAOut == 0 ? TRUE : FALSE;
	flags.neg = ULAOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}









verificar o carry
verificar o overflow

commitar

