#include "unit_control.h"

UC uc;

void UC_run(){
    int state = 0;
    while(1){
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

void UC_start(){
    uc.TYPE_OP = (char*) &mi.output;
    strcpy(uc.OP_ALU, "00000");
    strcpy(uc.OP_TF, "111");
    uc.W_RB = 0;
    uc.W_DM = 0;
    uc.W_RF = 0;
    uc.W_MI = 0;
}

void IF(){
    W_MI(1);
}

void ID(){
    char *type = (char*) substring(uc.TYPE_OP,0,2);
    if(strEquals(type,"001")){//ULA OP
        W_RB(0);//register fetch

        uc.OP_ALU = substring(uc.TYPE_OP,3,7);
        uc.OP_TF = "111";
        uc.W_RB = 1;
        uc.W_DM = 0;

        // Define o sinal que define quais flags serão atualizadas
        if(strEquals(uc.OP_ALU, "10011") //passb
        || strEquals(uc.OP_ALU, "11111")) //ones
            uc.W_RF = 0; // Não atualiza nenhuma
        else if(strEquals(uc.OP_ALU, "10000")) //zeros
            uc.W_RF = 1; // Atualiza Z
        else if(startWith(uc.OP_ALU, "01"))
            uc.W_RF = 3; // Atualiza S C Z
        else if(startWith(uc.OP_ALU, "00"))
            uc.W_RF = 4; // Atualiza O S C Z
        else
            uc.W_RF = 2; // Atualiza S Z

    }else if(strEquals(type,"010")){//CONS OP
        OP_SE(1);

        uc.OP_ALU = substring(uc.TYPE_OP,3,7);
        uc.OP_TF = "111";
        uc.W_RB = 1;
        uc.W_DM = 0;
        uc.W_RF = 0;
    }else if(strEquals(type,"100")){//MEM OP
        W_RB(0);

        uc.OP_TF = "111";
        uc.W_RB = (uc.TYPE_OP[7] == '0') ? 1 : 0; //load ativa o rb
        uc.W_DM = (uc.TYPE_OP[7] == '1') ? 1 : 0; //store ativa o dm
        uc.W_RF = 0;
    }else if(strEquals(type,"000")){//DES
        OP_SE(0);

        strcpy(uc.OP_ALU, "10011");
        uc.OP_TF = substring(uc.TYPE_OP,5,7);
        uc.W_RB = 0;
        uc.W_DM = 0;
        uc.W_RF = 0;
    }else if(strEquals(type,"110")){//DES RG
        W_RB(0);

        strcpy(uc.OP_ALU, "10011");
        uc.OP_TF = substring(uc.TYPE_OP,5,7);

        uc.W_RB = (uc.OP_TF[0] == '1')
        ? 0  //jal
        : 1; //jr

        uc.W_DM = 0;
        uc.W_RF = 0;
    }
}

void EX(){
    OP_ALU(uc.OP_ALU);
    W_DM(uc.W_DM);
    OP_TF(uc.OP_TF);
}

void WB(){
    W_RF(uc.W_RF);
    W_RB(uc.W_RB);
    W_PC(1);
}
