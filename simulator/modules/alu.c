#include "alu.h"

ALU alu;

char *adder_or_subtractor(int type, char *a,char *b,char *carryOut);

char *and(char *a, char *b);
char *or(char *a, char *b);
char *not(char *a);
char *xor(char *a);

void ALU_start(){
    alu.input_A = (char*) &rbank.output_PRA;
    alu.input_B = (char*) &rbank.output_PRB;
}

void OP_ALU(char *operation){
    if(strEquals(operation,"00000")){ //add
        strcpy(alu.result, adder_or_subtractor(0, alu.input_A,alu.input_B,alu.flags[2]));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"00001")){ //addi
        strcpy(alu.result, adder_or_subtractor(0, alu.input_A,alu.input_B,alu.flags[2]));
        strcpy(alu.result, adder_or_subtractor(0, alu.result,"00000000000000000000000000000001",alu.flags[2]));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"00011")){ //inca
        strcpy(alu.result, adder_or_subtractor(0, alu.input_A,"00000000000000000000000000000001",alu.flags[2]));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"00100")){ //subdec
        strcpy(alu.result, adder_or_subtractor(1, alu.input_A,alu.input_B,alu.flags[2]));
        strcpy(alu.result, adder_or_subtractor(1, alu.result,"00000000000000000000000000000001",alu.flags[2]));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"00101")){ //sub
        strcpy(alu.result, adder_or_subtractor(1, alu.input_A,alu.input_B,alu.flags[2]));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"00110")){ //deca
        strcpy(alu.result, adder_or_subtractor(1, alu.input_A,"00000000000000000000000000000001",alu.flags[2]));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"01000")){ //lsl
        strcpy(alu.result, strcat(substring(alu.input_A, 1, 31), "0"));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[2] = alu.intput_A[0]; //carry
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"01001")){ //asr
        strcpy(alu.result, strcat(substring(alu.input_A, 0, 0), substring(alu.input_A, 0, 30)));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[2] = alu.intput_A[31]; //carry
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"10000")){ //zeros
        strcpy(alu.result, ZERO);
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"10001")){ //and
        strcpy(alu.result, and(alu.input_A, alu.input_B));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"10010")){ //andnota
        strcpy(alu.result, and(not(alu.input_A), alu.input_B));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"10011")){ //passb
        strcpy(alu.result, alu.input_B);

    }else if(strEquals(operation,"10100")){ //andnotb
        strcpy(alu.result, and(alu.input_A, not(alu.input_B)));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"10101")){ //passa
        strcpy(alu.result, alu.input_A);
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"10110")){ //xor
        strcpy(alu.result, xor(alu.input_A, alu.input_B));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"10111")){ //or
        strcpy(alu.result, or(alu.input_A, alu.input_B));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"11000")){ //nand
        strcpy(alu.result, not(and(alu.input_A, alu.input_B)));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"11001")){ //xnor
        strcpy(alu.result, not(xor(alu.input_A, alu.input_B)));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"11010")){ //passnota
        strcpy(alu.result, not(alu.input_A));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"11011")){ //ornota
        strcpy(alu.result, or(not(alu.input_A), alu.input_B));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"11100")){ //passnotb
        strcpy(alu.result, not(alu.input_B));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"11101")){ //ornotb
        strcpy(alu.result, or(alu.input_A, not(alu.input_B)));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"11110")){ //nor
        strcpy(alu.result, not(or(alu.input_A, alu.input_B)));
        alu.flags[1] = (alu.result[0] == '0') ? 0 : 1; //sinal
        alu.flags[3] = (strEquls(alu.result, ZERO)) ? 1 : 0; //zero

    }else if(strEquals(operation,"11111")){ //ones
        strcpy(alu.result, "00000000000000000000000000000001");

    }else if(strEquals(operation,"01100")){ //loadlit
        strcpy(alu.result, alu.input_B);

    }else if(strEquals(operation,"01101")){ //lcl
        strcpy(alu.result, or(alu.input_B, and(alu.input_A, "11111111111111110000000000000000")));

    }else if(strEquals(operation,"01110")){ //lch
        strcpy(alu.result, or(strcat(substring(alu.input_B, 0, 15), "0000000000000000"), and(alu.input_A, "00000000000000001111111111111111")));
    }
}

char fullSubtractor(char ci,char a,char b,char *carryOut){
    if(ci == '0'){
        if(a==b){
            *co = '0';
            return '0';
        }else{
            if(a=='0'){
                *co = '1';
            }else {
                *co = '0';
            }
            return '1';
        }
    }else {
        if(a!=b){
            *co = '0';
            return '0';
        }else{
            if(a=='0'){
                *co = '0';
            }else {
                *co = '1';
            }
            return '1';
        }
    }
}

char fullAdder(char ci,char a,char b,char *carryOut){
    if(ci == '0'){
        if(a!=b){
            *co = '0';
            return '1';
        }else{
            if(a=='0'){//a ou b ja q sao iguais
                *co = '0';
            }else {//a ou b ja q sao iguais
                *co = '1';
            }
            return '0';
        }
    }else {
        if(a!=b){
            *co = '1';
            return '0';
        }else{
            if(a=='0'){//a ou b ja q sao iguais
                *co = '0';
            }else {//a ou b ja q sao iguais
                *co = '1';
            }
            return '1';
        }
    }
}

char *adder_or_subtractor(int type, char *a,char *b,char *carryOut){
    char *result = malloc(33);
    char carryIn = '0', cOut = '0';

    int i = strlen(a)-1;
    for(i;i>=0;i--){
        if(type == 1) {
            result[i]=fullSubtractor(carryIn,a[i],b[i],&cOut);
        } else {
            result[i]=fullAdder(carryIn,a[i],b[i],&cOut);
        }

        carryIn = cOut;//passa a diante o valor do carry
    }

    *cof = co;
    result[32] = '\0';
    return result;
}
char *and(char *a, char *b){
    if(a==b && a=='1')
        return '1';
    return '0';
}
char *or(char *a, char *b){
    if(a==b && a=='0')
        return '0';
    return '1';
}
char *not(char *a){
    if(a=='1')
        return '0';
    return '1';
}
char *xor(char *a){
    if(a==b)
        return '0';
    return '1';
}
