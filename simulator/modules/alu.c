#include "alu.h"

ALU alu;

//Função que executa uma operação AND bit a bit dos operandos 'a' e 'b'
char *and(char *a, char *b);
//Função que executa uma operação OR bit a bit dos operandos 'a' e 'b'
char *or(char *a, char *b);
//Função que executa uma operação XOR bit a bit dos operandos 'a' e 'b'
char *xor(char *a, char *b);
//Função que executa uma operação NOT bit a bit do operando 'a'
char *not(char *a);

//Função que executa uma operação de adição ou subtração, indicada por 'type'
char *adder_or_subtractor(int type, char *a, char *b, char *carryOut);

void OP_ALU(char *operation) {
    if(strEquals(operation, "00000")) {
    //add c, a, b <=> c = a + b
        strcpy(alu.output, adder_or_subtractor(0, alu.input_A, alu.input_B, &alu.flags[2]));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "00001")) {
    //addi c, a, b <=> c = a + b + 1
        strcpy(alu.output, adder_or_subtractor(0, alu.input_A, alu.input_B, &alu.flags[2]));
        strcpy(alu.output, adder_or_subtractor(0, alu.output, "00000000000000000000000000000001", &alu.flags[2]));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "00011")) {
    //inca c, a <=> c = a + 1
        strcpy(alu.output, adder_or_subtractor(0, alu.input_A, "00000000000000000000000000000001", &alu.flags[2]));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "00100")) {
    //subdec c, a, b <=> c = a - b - 1
        strcpy(alu.output, adder_or_subtractor(1, alu.input_A, alu.input_B, &alu.flags[2]));
        strcpy(alu.output, adder_or_subtractor(1, alu.output, "00000000000000000000000000000001", &alu.flags[2]));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "00101")) {
    //sub c, a, b <=> c = a - b
        strcpy(alu.output, adder_or_subtractor(1, alu.input_A, alu.input_B, &alu.flags[2]));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "00110")) {
    //deca c, a <=> c = a - 1
        strcpy(alu.output, adder_or_subtractor(1, alu.input_A, "00000000000000000000000000000001", &alu.flags[2]));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "01000")) {
    //lsl c, a <=> c = << a
        char *shifted = malloc(33);
        sprintf(shifted, "%s0", substring(alu.input_A, 1, 31));
        strcpy(alu.output, shifted);
        
        alu.flags[1] = alu.output[0];
        alu.flags[2] = alu.input_A[0]; //carry
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "01001")) {
    //asr c, a <=> c = >> a
        char *shifted = malloc(33);
        sprintf(shifted, "%s%s", substring(alu.input_A, 0, 0), substring(alu.input_A, 0, 30));
        strcpy(alu.output, shifted);
        
        alu.flags[1] = alu.output[0];
        alu.flags[2] = alu.input_A[31]; //carry
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "10000")) {
    //zeros c <=> c = 0
        strcpy(alu.output, ZERO);
        
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "10001")) {
    //and c, a, b <=> c = a & b
        strcpy(alu.output, and(alu.input_A, alu.input_B));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "10010")) {
    //andnota c, a, b <=> c = !a & b
        strcpy(alu.output, and(not(alu.input_A), alu.input_B));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "10011")) {
    //passb c, b <=> c = b
        strcpy(alu.output, alu.input_B);

    } else if(strEquals(operation, "10100")) {
    //andnotb c, a, b <=> c = a & !b
        strcpy(alu.output, and(alu.input_A, not(alu.input_B)));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "10101")) {
    //passa c, a <=> c = a
        strcpy(alu.output, alu.input_A);
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "10110")) {
    //xor c, a, b <=> c = a xor b
        strcpy(alu.output, xor(alu.input_A, alu.input_B));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "10111")) {
    //or c, a, b <=> c = a | b
        strcpy(alu.output, or(alu.input_A, alu.input_B));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "11000")) {
    //nand c, a, b <=> c = !(a & b)
        strcpy(alu.output, not(and(alu.input_A, alu.input_B)));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "11001")) {
    //xnor c, a, b <=> c = !(a xor b)
        strcpy(alu.output, not(xor(alu.input_A, alu.input_B)));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "11010")) {
    //passnota c, a <=> c = !a
        strcpy(alu.output, not(alu.input_A));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "11011")) {
    //ornota c, a, b <=> c = !a | b
        strcpy(alu.output, or(not(alu.input_A), alu.input_B));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "11100")) {
    //passnotb c, b <=> c = !b
        strcpy(alu.output, not(alu.input_B));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "11101")) {
    //ornotb c, a, b <=> c = a | !b
        strcpy(alu.output, or(alu.input_A, not(alu.input_B)));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "11110")) {
    //nor c, a, b <=> c = !(a | b)
        strcpy(alu.output, not(or(alu.input_A, alu.input_B)));
        
        alu.flags[1] = alu.output[0];
        alu.flags[3] = (strEquals(alu.output, ZERO)) ? '1' : '0';

    } else if(strEquals(operation, "11111")) {
    //ones c <=> c = 1
        strcpy(alu.output, "00000000000000000000000000000001");

    } else if(strEquals(operation, "01100")) {
    //loadlit c, Const <=> c = Const
        strcpy(alu.output, alu.input_B);

    } else if(strEquals(operation, "01101")) {
    //lcl c, Const <=> c = Const16 | (C&0xffff0000)
    //o 'C' de (C&0xffff0000) é posto em input_A pelo assembler
        strcpy(alu.output, or(alu.input_B, and(alu.input_A, "11111111111111110000000000000000")));

    } else if(strEquals(operation, "01110")) {
    //lch c, Const <=> c = (Const16 « 16) | (C&0xffff0000)
    //o 'C' de (C&0xffff0000) é posto em input_A pelo assembler
        char Const16_16[33] = "00000000000000000000000000000000";
        int x;
        for(x = 0; x < 16; x++) {
            Const16_16[x] = alu.input_B[x];
        }
        
        char *Ce0xffff0000 = and(alu.input_A, "00000000000000001111111111111111");

        strcpy(alu.output, or(Const16_16, Ce0xffff0000));
    }
}

void RST_ALU(char value) {
    if(value == '1') {
        strcpy(alu.output, ZERO); //Zera a saída 'alu.output'
        //Zera as flags
        alu.flags[0] = '0';
        alu.flags[1] = '0';
        alu.flags[2] = '0';
        alu.flags[3] = '0';
    }
}

char *and(char a[33], char b[33]) {
    char *result = malloc(33);
    int x;

    for(x = 0; x < 33; x++) {
        result[x] = (a[x]==b[x]) ? a[x] : '0'; 
    }
    result[x] = '\0';

    return result;
}

char *or(char a[33], char b[33]) {
    char *result = malloc(33);
    int x;

    for(x = 0; x < 33; x++) {
        result[x] = (a[x]==b[x]) ? a[x] : '1'; 
    }
    result[x] = '\0';

    return result;
}

char *xor(char a[33], char b[33]) {
    char *result = malloc(33);
    int x;

    for(x = 0; x < 33; x++) {
        result[x] = (a[x]==b[x]) ? '0' : '1'; 
    }
    result[x] = '\0';

    return result;
}

char *not(char a[33]) {
    char *result = malloc(33);
    int x;

    for(x = 0; x < 33; x++) {
        result[x] = (a[x]=='0') ? '1' : '0'; 
    }
    result[x] = '\0';

    return result;
}

/*
    Função que representa um subtrator completo. Retorna o resultado
    de 'a' - 'b' e atribui o carry, quando houver, em 'carryOut'
*/
char fullSubtractor(char carryIn, char a, char b, char *carryOut) {
    if(carryIn == '0') {
        if(a == b) {
            *carryOut = '0';
            return '0';
        } else {
            *carryOut = b;
            return '1';
        }
    } else {
        if(a == b) {
            *carryOut = '1';
            return '1';
        } else {
            *carryOut = b;
            return '0';
        }
    }
}

/*
    Função que representa um somador completo. Retorna o resultado
    de 'a' + 'b' e atribui o carry, quando houver, em 'carryOut'
*/
char fullAdder(char carryIn, char a, char b, char *carryOut) {
    if(carryIn == '0') {
        if(a != b) {
            *carryOut = '0';
            return '1';
        } else {
            *carryOut = b;
            return '0';
        }
    } else {
        if(a != b) {
            *carryOut = '1';
            return '0';
        } else {
            *carryOut = b;
            return '1';
        }
    }
}

char *adder_or_subtractor(int type, char *a, char *b, char *carryOut) {
    char *result = malloc(33);
    char carryIn = '0', cOut = '0';

    int i = strlen(a)-1;
    for(i;i>=0;i--) {
        if(type == 1) {
            result[i]=fullSubtractor(carryIn,a[i],b[i],&cOut);
        } else {
            result[i]=fullAdder(carryIn,a[i],b[i],&cOut);
        }

        carryIn = cOut;
    }

    *carryOut = cOut;
    result[32] = '\0';
    return result;
}