#include "alu.h"

ALU alu;

void ALU_start(){
    alu.input_A = (*char) &rbank.output_PRA;
    alu.input_B = (*char) &rbank.output_PRB;
}

void OP_ALU(char operation)){
    switch (strEquals(operation, "10011") {
        case /* value */:
    }
}
