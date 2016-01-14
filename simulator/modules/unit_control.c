#include "unit_control.h"

UC uc;

void print();

void UC_start() {}

void UC_run(){
    print();
    int nextstate;
    int state = 0;
    for(;;){
        switch (state) {
            case 0:
                IF();
                nextstate = 1;
            break;
            case 1:
                ID();
                nextstate = 2;
            break;
            case 2:
                EX();
                nextstate = 3;
            break;
            case 3:
                WB();
                nextstate = 0;
            break;
        }
        state = nextstate;
    }
}

void IF(){}

void ID(){
    /*if(){ //op logica aritmetica

    } else if(){ //op constantes

    }else if(){ //op com memoria

    }else if(){ //op com jump

    }else if(){ //especiais

    }*/
}

void EX(){

}

void WB(){

}

void print() {
    system("cls");

    printf("==========================\n");
    printf("----------- PC -----------\n");
    printf("==========================\n");
    printf("\n\n");

    printf("==========================\n");
    printf("----------- MI -----------\n");
    printf("==========================\n");
    printf("\n\n");

    printf("==========================\n");
    printf("----------- UC -----------\n");
    printf("==========================\n");
    printf("\n\n");

    printf("==========================\n");
    printf("----------- RB -----------\n");
    printf("==========================\n");
    printf("R0:  %s\n", rbank.registers[0]);
    printf("R1:  %s\n", rbank.registers[1]);
    printf("R2:  %s\n", rbank.registers[2]);
    printf("R3:  %s\n", rbank.registers[3]);
    printf("R4:  %s\n", rbank.registers[4]);
    printf("R5:  %s\n", rbank.registers[5]);
    printf("R6:  %s\n", rbank.registers[6]);
    printf("R7:  %s\n", rbank.registers[7]);
    printf("R8:  %s\n", rbank.registers[8]);
    printf("R9:  %s\n", rbank.registers[9]);
    printf("R10: %s\n", rbank.registers[10]);
    printf("R11: %s\n", rbank.registers[11]);
    printf("R12: %s\n", rbank.registers[12]);
    printf("R13: %s\n", rbank.registers[13]);
    printf("R14: %s\n", rbank.registers[14]);
    printf("R15: %s\n", rbank.registers[15]);
    printf("\n\n");

    printf("==========================\n");
    printf("----------- DM -----------\n");
    printf("==========================\n");
    printf("\n\n");

    printf("==========================\n");
    printf("----------- SE -----------\n");
    printf("==========================\n");
    printf("\n\n");

    printf("==========================\n");
    printf("----------- ALU ----------\n");
    printf("==========================\n");
    printf("\n\n");

    printf("==========================\n");
    printf("----------- RF -----------\n");
    printf("==========================\n");
    printf("\n\n");

    printf("==========================\n");
    printf("----------- TF -----------\n");
    printf("==========================\n");
    printf("\n\n");
}