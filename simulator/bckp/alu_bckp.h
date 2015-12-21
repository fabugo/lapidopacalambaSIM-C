void ExAlu(){
	switch(controlAlu){
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
		case 25: loadlit();	 break;
		case 26: lcl();	     break;
        case 27: lch();	     break;
		case 28: load();	 break;
		case 29: store();	 break;
        case 30: j();	     break;
		case 31: jf();	     break;
		case 32: jt();	     break;
		case 33: jal();	     break;
		case 34: jr();	     break;
	}
}

void add(){
	ALUOut = A + B;
	flags.zero = ALUOut == 0 ? TRUE:FALSE;
	flags.neg = ALUOut < 0 ? TRUE:FALSE;
	flags.negzero = flags.zero || flags.neg ? TRUE:FALSE;
	flags.overflow = verifyOverflow(ALUOut, A, B);
	flags.carry = verifyCarry(ALUOut, A, B);
}

void addinc(){
	ALUOut =  A + B + 1;
	flags.zero = ALUOut == 0 ? TRUE:FALSE;
	flags.neg = ALUOut < 0 ? TRUE:FALSE;
	flags.negzero = flags.zero || flags.neg) ? TRUE:FALSE;
	flags.overflow = verifyOverflow(ALUOut, A, B);
	flags.carry = verifyCarry(ALUOut, A, B);
}

void inca(){
	ALUOut = A + 1;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = verifyOverflow(ALUOut, A, B);
	flags.carry = verifyCarry(ALUOut, A, 1);
}

void subdec(){
	ALUOut = A - B - 1;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = verifyOverflow(ALUOut, A, B);
	flags.carry = verifyCarry(ALUOut, A, -B);
}

void sub(){
	ALUOut = A - B;
	flags.zero = ALUOut == 0;
	flags.neg = ALUOut < 0;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = verifyOverflow(ALUOut, A, B);
	flags.carry = verifyCarry(ALUOut, A, -B);
}

void deca(){
	ALUOut = A - 1;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = verifyOverflow(ALUOut, A, B);
	flags.carry = verifyCarry(ALUOut, A, -1);
}

void lsl(){
	ALUOut = A << 1;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = ;
}

void asr(){
	ALUOut = A >> 1;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = ;
}

void zeros(){
	ALUOut = 0;
	flags.zero = TRUE;
	flags.neg = FALSE;
	flags.negzero = TRUE;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void and(){
	ALUOut = A & B;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void andnota(){
	ALUOut = (~A) & B;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void passb(){
    ALUOut = B;
	flags.zero = FALSE;
	flags.neg = FALSE;
	flags.negzero = FALSE;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void andnotb(){
    ALUOut = A & (~B);
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void passa(){
	ALUOut = A;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void xor(){
	ALUOut = A ^ B;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void or(){
	ALUOut = A | B;
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void nand(){
	ALUOut = ~(aluA & aluB); // execuÃ§Ã£o
	alu_flags.zero = ALUOut == 0 ? TRUE : FALSE;
	alu_flags.neg = ALUOut < 0 ? TRUE : FALSE;
	alu_flags.negzero = alu_flags.zero || alu_flags.neg;
	alu_flags.overflow = FALSE;
	alu_flags.carry = FALSE;
}

void xnor(){
	ALUOut = ~(A ^ B);
	flags.zero = ALUOut == 0  ? TRUE : FALSE;
	flags.neg = ALUOut < 0;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void passnota(){
	ALUOut = ~A;
	flags.zero = ALUOut == 0  ? TRUE : FALSE;
	flags.neg = ALUOut < 0  ? TRUE : FALSE;
	flags.negzero = alu_flags.zero || alu_flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void ornota(){
    ALUOut = ~A | B;
	flags.zero = ALUOut == 0  ? TRUE : FALSE;
	flags.neg = ALUOut < 0  ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;

}

void passnotb(){
    ALUOut = B;
    flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void ornotb(){
	ALUOut = A | ~B;
	flags.zero = ALUOut == 0  ? TRUE : FALSE;
	flags.neg = ALUOut < 0  ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void nor(){
	ALUOut = ~(A | B);
	flags.zero = ALUOut == 0 ? TRUE : FALSE;
	flags.neg = ALUOut < 0 ? TRUE : FALSE;
	flags.negzero = flags.zero || flags.neg;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void ones(){
	ALUOut = 1;
	flags.zero = FALSE;
	flags.neg = FALSE;
	flags.negzero = FALSE;
	flags.overflow = FALSE;
	flags.carry = FALSE;
}

void loadlit(){
    ALUOut = B // em B estará a constante.
}

void lcl(){
	ALUOut = B | (B & 0xffff0000);
}

void lch(){
	ALUOut = (B << 16) | (B & 0x0000ffff);
}

void load(){
	//??
}

void store(){
	//??
}

void j(){
	ALUOut = B; // sendo que B deve conter o endereço
}

void jf(){
	ALUOut = B; // sendo que B deve conter o endereço
}

void jt(){
	ALUOut = B; // sendo que B deve conter o endereço
}

void jal(){
	ALUOut = B; // sendo que B deve conter o endereço
}

void jr(){
	ALUOut = B; // sendo que B deve conter o endereço
}


bool verifyCarry(int ALUOut, int A, int B){
    //fazer a função do carry

}

bool verifyOverflow(int ALUOut, int A, int B){
    bool b = true;
    if((ALUOut<0 & (A>0&B>0)) || (ALUOut>0 & (A<0&B<0))){
	   b = TRUE;
    }
    else{
       b = FALSE;
    }
    return b;
}

