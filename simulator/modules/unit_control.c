#include "unit_control.h"

UC uc;

//Função para a parte Instruction Fetch
void IF();
//Função para a parte Identification
void ID();
//Função para a parte Execution
void EX();
//Função para a parte Write Bank
void WB();

//Função não existente em um processador real, mas aqui é usada. Ela imprime na tela
//o estado atual de todo o processador.
void print();

void UC_run() {
    int state = 0;
    print();
    while(1) {
        switch (state) {
            case 0:
                IF();
                state = 1;
            break;
            case 1:
                ID();
                state = 2;
            break;
            case 2:
                EX();
                state = 3;
            break;
            case 3:
                WB();
                state = 0;
            break;
        }
    }
}

void IF() {
    W_MI('1');
    ADD_PC('1');
}

void ID() {
    char *type = (char*) substring(uc.TYPE_OP,0,2);
    if(strEquals(type,"001")) {         //ULA OP
        W_RB('0');//register fetch
        strcpy(uc.OP_ALU, substring(uc.TYPE_OP,3,7));
        strcpy(uc.OP_TF, "111");
        uc.W_RB = '1';
        uc.W_DM = '0';
        uc.S_MXSE = '0';
        strcpy(uc.S_MXRB, "10");

        // Define o sinal que define quais flags serão atualizadas
        if(strEquals(uc.OP_ALU, "10011")        //passb
        || strEquals(uc.OP_ALU, "11111"))       //ones
            strcpy(uc.W_RF, "000"); // Não atualiza nenhuma
        else if(strEquals(uc.OP_ALU, "10000"))  //zeros
            strcpy(uc.W_RF, "001"); // Atualiza Z
        else if(startWith(uc.OP_ALU, "01"))
            strcpy(uc.W_RF, "011"); // Atualiza S C Z
        else if(startWith(uc.OP_ALU, "00"))
            strcpy(uc.W_RF, "100"); // Atualiza O S C Z
        else
            strcpy(uc.W_RF, "010"); // Atualiza S Z

    } else if(strEquals(type,"010")) {  //CONS OP
        W_RB('0');
        OP_SE('1');
        strcpy(uc.OP_ALU, substring(uc.TYPE_OP, 3, 7));
        strcpy(uc.OP_TF, "111");
        uc.W_RB = '1';
        uc.W_DM = '0';
        strcpy(uc.W_RF, "000");
        uc.S_MXSE = '1';
        strcpy(uc.S_MXRB, "10");
    } else if(strEquals(type,"100")) {  //MEMORY OP
        W_RB('0');
        strcpy(uc.OP_TF, "111");
        uc.W_RB = (uc.TYPE_OP[7] == '0') ? '1' : '0'; //load ativa o rb
        uc.W_DM = uc.TYPE_OP[7]; //0 - leitura, 1 - escrita
        strcpy(uc.W_RF, "000");
        uc.S_MXSE = '0';
        strcpy(uc.S_MXRB, "01");
    } else if(strEquals(type,"000")) {  //JUMPER OP
        OP_SE('0');
        strcpy(uc.OP_ALU, "10011"); //passb
        strcpy(uc.OP_TF, substring(uc.TYPE_OP, 5, 7));
        uc.W_RB = '0';
        uc.W_DM = '0';
        uc.S_MXSE = '1';
        strcpy(uc.W_RF, "000");
    } else if(strEquals(type,"110")) {  //JUMPER REGISTER OP
        W_RB('0');
        strcpy(uc.OP_ALU, "10011"); //passb
        strcpy(uc.OP_TF, substring(uc.TYPE_OP, 5, 7));
        uc.W_RB = (strEquals(uc.OP_TF, "001")) ? '1' : '0'
        ? '0'  //jal
        : '1'; //jr
        uc.W_DM = '0';
        strcpy(uc.W_RF, "000");
        strcpy(uc.S_MXRB, "00");
    }
}

void EX() {
    S_MXSE(uc.S_MXSE);
    OP_ALU(uc.OP_ALU);
    W_DM(uc.W_DM);
    OP_TF(uc.OP_TF);
}

void WB() {
    S_MXRB(uc.S_MXRB);
    S_MXPC(tf.output);
    W_RF(uc.W_RF);
    W_RB(uc.W_RB);
    print();
    W_PC('1');
}

void print() {
    system("cls");

    printf("======================================== || ======================================== || ======================================== ||\n");
    printf("------------------ PC ------------------ || ------------------ RB ------------------ || ------------------ DM ------------------ ||\n");
    printf("======================================== || ======================================== || ======================================== ||\n");
    printf("in    : %s || R0    : %s || 0     : %s ||\n", pc.input, rbank.registers[0], dm.data[0]);
    printf("out   : %s || R1    : %s || 1     : %s ||\n", pc.output, rbank.registers[1], dm.data[1]);
    printf("                                         || R2    : %s || 2     : %s ||\n", rbank.registers[2], dm.data[2]);
    printf("======================================== || R3    : %s || 3     : %s ||\n", rbank.registers[3], dm.data[2]);
    printf("------------------ MI ------------------ || R4    : %s || 4     : %s ||\n", rbank.registers[4], dm.data[4]);
    printf("======================================== || R5    : %s || 5     : %s ||\n", rbank.registers[5], dm.data[5]);
    printf("in  RI: %s || R6    : %s || 6     : %s ||\n", mi.input, rbank.registers[6], dm.data[6]);
    printf("out  I: %s || R7    : %s || 7     : %s ||\n", mi.output, rbank.registers[7], dm.data[7]);
    printf("                                         || R8    : %s || 8     : %s ||\n", rbank.registers[8], dm.data[8]);
    printf("                                         || R9    : %s || 9     : %s ||\n", rbank.registers[9], dm.data[9]);
    printf("                                         || R10   : %s || 10    : %s ||\n", rbank.registers[10], dm.data[10]);
    printf("                                         || R11   : %s || 11    : %s ||\n", rbank.registers[11], dm.data[11]);
    printf("                                         || R12   : %s || 12    : %s ||\n", rbank.registers[12], dm.data[12]);
    printf("                                         || R13   : %s || 13    : %s ||\n", rbank.registers[13], dm.data[13]);
    printf("                                         || R14   : %s || 14    : %s ||\n", rbank.registers[14], dm.data[14]);
    printf("                                         || R15   : %s || 15    : %s ||\n", rbank.registers[15], dm.data[15]);
    printf("======================================== || in RA : %s                             || in WP : %s ||\n", substring(rbank.input_RA, 12, 15), dm.input);
    printf("------------------ SE ------------------ || in RB : %s                             || in AD : %s ||\n", substring(rbank.input_RB, 16, 19), dm.address);
    printf("======================================== || in WC : %s                             || out PR: %s ||\n", substring(rbank.input_WC, 8, 11), dm.output);
    printf("in    : %s || ou WPC: %s ||\n", se.input, rbank.input_WPC);
    printf("out   : %s || ou PRA: %s ||\n", se.output, rbank.output_PRA);
    printf("                                         || ou PRB: %s ||\n", rbank.output_PRB);
    /*IMPRIMIR A MEMÓRIA DE INSTRUÇÕES EM ARQUIVO*/
    /*IMPRIMIR A MEMÓRIA DE DADOS EM ARQUIVO*/
    printf("\n");
    
    printf("======================================== || ======================================== || ========================================\n");
    printf("------------------ ALU ----------------- || ------------------ RF ------------------ || ------------------ TF ------------------\n");
    printf("======================================== || ======================================== || ========================================\n");
    printf("in A  : %s || in O  : %c                                || in O  : %c\n", alu.input_A, rf.input_flags[0], tf.input_flags[0]);
    printf("in B  : %s || in S  : %c                                || in S  : %c\n", alu.input_B, rf.input_flags[1], tf.input_flags[1]);
    printf("out C : %s || in C  : %c                                || in C  : %c\n", alu.output, rf.input_flags[2], tf.input_flags[2]);
    printf("flag O: %c                                || in Z  : %c                                || in Z  : %c\n", alu.flags[0], rf.input_flags[3], tf.input_flags[3]);
    printf("flag S: %c                                || out O : %c                                || COND  : %s\n", alu.flags[1], rf.output_flags[0], substring(tf.cond, 17, 19));
    printf("flag C: %c                                || out S : %c                                || out   : %c\n", alu.flags[2], rf.output_flags[1], tf.output);
    printf("flag Z: %c                                || out C : %c                                ||\n", alu.flags[3], rf.output_flags[2]);
    printf("                                         || out Z : %c                                ||\n", rf.output_flags[3]);
    printf("\n");

    printf("======================================== || ======================================== || ========================================\n");
    printf("----------------- MX_PC ---------------- || ----------------- MX_RB ---------------- || ----------------- MX_SE ----------------\n");
    printf("======================================== || ======================================== || ========================================\n");
    printf("in ALU: %s || in PC : %s || in RB : %s\n", mx_pc.input_ALU, mx_rb.input_PC, mx_se.input_RB);
    printf("in PC : %s || in DM : %s || in SE : %s\n", mx_pc.input_ADD, mx_rb.input_DM, mx_se.input_SE);
    printf("out   : %s || in ALU: %s || out   : %s\n", mx_pc.output, mx_rb.input_ALU, mx_se.output);
    printf("                                         || out   : %s ||\n", mx_rb.output);
    printf("\n");

    system("pause");
}