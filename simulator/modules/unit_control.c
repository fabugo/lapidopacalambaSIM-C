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

int count = 0;

void print() {
    if(count != 0 && !(count > 1000)) { //Condições para imprimir
        count++;
        return;
    }

    system("cls");
    printf("Instrucoes Executadas: %d\n", count++);

    printf("======================================== || ======================================== || ======================================== ||\n");
    printf("------------------ PC ------------------ || ------------------ RB ------------------ || ------------------ DM ------------------ ||\n");
    printf("======================================== || ======================================== || ======================================== ||\n");
    printf("in    : %32s || R0    : %32s || 0     : %32s ||\n", pc.input, rbank.registers[0], dm.data[0]);
    printf("out   : %32s || R1    : %32s || 1     : %32s ||\n", pc.output, rbank.registers[1], dm.data[1]);
    printf("                                         || R2    : %32s || 2     : %32s ||\n", rbank.registers[2], dm.data[2]);
    printf("======================================== || R3    : %32s || 3     : %32s ||\n", rbank.registers[3], dm.data[3]);
    printf("------------------ MI ------------------ || R4    : %32s || 4     : %32s ||\n", rbank.registers[4], dm.data[4]);
    printf("======================================== || R5    : %32s || 5     : %32s ||\n", rbank.registers[5], dm.data[5]);
    printf("in  RI: %32s || R6    : %32s || 6     : %32s ||\n", mi.input, rbank.registers[6], dm.data[6]);
    printf("out  I: %32s || R7    : %32s || 7     : %32s ||\n", mi.output, rbank.registers[7], dm.data[7]);
    printf("                                         || R8    : %32s || 8     : %32s ||\n", rbank.registers[8], dm.data[8]);
    printf("                                         || R9    : %32s || 9     : %32s ||\n", rbank.registers[9], dm.data[9]);
    printf("                                         || R10   : %32s || 10    : %32s ||\n", rbank.registers[10], dm.data[10]);
    printf("                                         || R11   : %32s || 11    : %32s ||\n", rbank.registers[11], dm.data[11]);
    printf("                                         || R12   : %32s || 12    : %32s ||\n", rbank.registers[12], dm.data[12]);
    printf("                                         || R13   : %32s || 13    : %32s ||\n", rbank.registers[13], dm.data[13]);
    printf("                                         || R14   : %32s || 14    : %32s ||\n", rbank.registers[14], dm.data[14]);
    printf("                                         || R15   : %32s || 15    : %32s ||\n", rbank.registers[15], dm.data[15]);
    printf("======================================== || in RA : %32s || in WP : %32s ||\n", substring(rbank.input_RA, 12, 15), dm.input);
    printf("------------------ SE ------------------ || in RB : %32s || in AD : %32s ||\n", substring(rbank.input_RB, 16, 19), dm.address);
    printf("======================================== || in WC : %32s || out PR: %32s ||\n", substring(rbank.input_WC, 8, 11), dm.output);
    printf("in    : %32s || ou WPC: %32s ||\n", se.input, rbank.input_WPC);
    printf("out   : %32s || ou PRA: %32s ||\n", se.output, rbank.output_PRA);
    printf("                                         || ou PRB: %32s ||\n", rbank.output_PRB);
    /*IMPRIMIR A MEMÓRIA DE INSTRUÇÕES EM ARQUIVO*/
    /*IMPRIMIR A MEMÓRIA DE DADOS EM ARQUIVO*/
    printf("\n");
    
    printf("======================================== || ======================================== || ========================================\n");
    printf("------------------ ALU ----------------- || ------------------ RF ------------------ || ------------------ TF ------------------\n");
    printf("======================================== || ======================================== || ========================================\n");
    printf("in A  : %32s || in O  : %32c || in O  : %32c\n", alu.input_A, rf.input_OSCZ[0], tf.input_OSCZ[0]);
    printf("in B  : %32s || in S  : %32c || in S  : %32c\n", alu.input_B, rf.input_OSCZ[1], tf.input_OSCZ[1]);
    printf("out C : %32s || in C  : %32c || in C  : %32c\n", alu.output, rf.input_OSCZ[2], tf.input_OSCZ[2]);
    printf("flag O: %32c || in Z  : %32c || in Z  : %32c\n", alu.OSCZ[0], rf.input_OSCZ[3], tf.input_OSCZ[3]);
    printf("flag S: %32c || out O : %32c || COND  : %32s\n", alu.OSCZ[1], rf.output_OSCZ[0], substring(tf.cond, 17, 19));
    printf("flag C: %32c || out S : %32c || out   : %32c\n", alu.OSCZ[2], rf.output_OSCZ[1], tf.output);
    printf("flag Z: %32c || out C : %32c ||\n", alu.OSCZ[3], rf.output_OSCZ[2]);
    printf("                                         || out Z : %32c ||\n", rf.output_OSCZ[3]);
    printf("\n");

    printf("======================================== || ======================================== || ========================================\n");
    printf("----------------- MX_PC ---------------- || ----------------- MX_RB ---------------- || ----------------- MX_SE ----------------\n");
    printf("======================================== || ======================================== || ========================================\n");
    printf("in ALU: %32s || in PC : %32s || in RB : %32s\n", mx_pc.input_ALU, mx_rb.input_PC, mx_se.input_RB);
    printf("in PC : %32s || in DM : %32s || in SE : %32s\n", mx_pc.input_ADD, mx_rb.input_DM, mx_se.input_SE);
    printf("out   : %32s || in ALU: %32s || out   : %32s\n", mx_pc.output, mx_rb.input_ALU, mx_se.output);
    printf("                                         || out   : %32s ||\n", mx_rb.output);
    printf("\n");

    system("pause");
}