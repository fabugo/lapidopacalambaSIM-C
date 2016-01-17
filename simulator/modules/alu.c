#include "alu.h"

ALU alu;

void ALU_start(){
    alu.input_A = (*char) &rbank.output_PRA;
    alu.input_B = (*char) &rbank.output_PRB;
}

void OP_ALU(char operation)){
    if(strEquals(operation,"00000")){
        
    }else if(strEquals(operation,"00001")){

    }else if(strEquals(operation,"00011")){

    }else if(strEquals(operation,"00100")){

    }else if(strEquals(operation,"00101")){

    }else if(strEquals(operation,"00110")){

    }else if(strEquals(operation,"01000")){

    }else if(strEquals(operation,"01001")){

    }else if(strEquals(operation,"10000")){

    }else if(strEquals(operation,"10001")){

    }else if(strEquals(operation,"10010")){

    }else if(strEquals(operation,"10011")){

    }else if(strEquals(operation,"10100")){

    }else if(strEquals(operation,"10101")){

    }else if(strEquals(operation,"10110")){

    }else if(strEquals(operation,"10111")){

    }else if(strEquals(operation,"11000")){

    }else if(strEquals(operation,"11001")){

    }else if(strEquals(operation,"11010")){

    }else if(strEquals(operation,"11011")){

    }else if(strEquals(operation,"11100")){

    }else if(strEquals(operation,"11101")){

    }else if(strEquals(operation,"11110")){

    }else if(strEquals(operation,"11111")){

    }else if(strEquals(operation,"01100")){

    }else if(strEquals(operation,"01101")){

    }else if(strEquals(operation,"01110")){

    }
}
