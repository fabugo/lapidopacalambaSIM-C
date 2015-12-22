#include "unit_control.h"

UC uc;

void UC_run(){
    UC_start();
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

void UC_start(){
    uc.TYPE_OP = (char*) mi.output;
}

void IF(){
    W_MI(1);
}

void ID(){
    //op logica aritmetica
    if(){

    }else
    //op constantes
    if(){

    }else
    //op com memoria
    if(){

    }else
    //op com jump
    if(){

    }else
    //especiais
    if(){

    }
}

void EX(){

}

void WB(){

}
