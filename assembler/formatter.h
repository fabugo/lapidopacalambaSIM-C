#include <stdio.h>
#include <string.h>

struct INSTRUCTION {
    int address;
    char *content;
    struct INSTRUCTION *previous;
    struct INSTRUCTION *next;
};
typedef struct INSTRUCTION Instruction;

int isRegistrator(char *string) {
    return (stringEquals(string, "r0") || stringEquals(string, "r1")
        || stringEquals(string, "r2") || stringEquals(string, "r3")
        || stringEquals(string, "r4") || stringEquals(string, "r5")
        || stringEquals(string, "r6") || stringEquals(string, "r7")
        || stringEquals(string, "r8") || stringEquals(string, "r9")
        || stringEquals(string, "r10") || stringEquals(string, "r11")
        || stringEquals(string, "r12") || stringEquals(string, "r13")
        || stringEquals(string, "r14") || stringEquals(string, "r14"))
    ? 1 : 0;
}

int isConstant(char *string) {
    int lenght = strlen(string);
    int x;
    for(x = 0; x < lenght; x++) { //Percorre toda a string verificando se há apenas números
        if(string[lenght] < '0' || string[lenght] > '9') {
            return 0;
        }
    }
    return 1;
}

int isLabel(char *string) {
    return isAlphanumeric(string);
}

//Verifica se uma instrução é válida de acordo com o ISA
int isValidInstruction(char *instruction) {
    int space = indexOf(instruction, ' ');
    if(space == -1) { //Apenas a instrução nop não possui espaço
        return stringEquals(instruction, "nop") ? 1 : 0;
    }

    char *instr = substring(instruction, 0, space-1);
    if(stringEquals(instr, "add") || stringEquals(instr, "addinc")
            || stringEquals(instr, "subdec") || stringEquals(instr, "sub")
            || stringEquals(instr, "and") || stringEquals(instr, "andnota")
            || stringEquals(instr, "andnotb") || stringEquals(instr, "xor")
            || stringEquals(instr, "or") || stringEquals(instr, "nand")
            || stringEquals(instr, "xnor") || stringEquals(instr, "ornata")
            || stringEquals(instr, "ornotb")) {

        char *params = removeAll(substring(instruction, space, strlen(instruction)), ' ');
        int lenght = strlen(params);

        if(lenght >= 8 && lenght <= 11) {
            int firstIndex = indexOf(params, ',');
            int lastIndex = lastIndexOf(params, ',');
            return ((firstIndex != -1 && lastIndex != -1 && firstIndex != lastIndex && lastIndex < lenght)
                && isRegistrator(substring(params, 0, firstIndex - 1))
                && isRegistrator(substring(params, firstIndex + 1, lastIndex - 1))
                && isRegistrator(substring(params, lastIndex + 1, lenght)))
            ? 1 : 0;
        }

        return 0;
    } else if(stringEquals(instr, "inca") || stringEquals(instr, "deca")
            || stringEquals(instr, "lsl") || stringEquals(instr, "asr")
            || stringEquals(instr, "passa") || stringEquals(instr, "passb")
            || stringEquals(instr, "passnota") || stringEquals(instr, "passnotb")
            || stringEquals(instr, "load") || stringEquals(instr, "store")) {

        char *params = removeAll(substring(instruction, space, strlen(instruction)), ' ');
        int lenght = strlen(params);
        if(lenght >= 5 && lenght <= 7) {
            int index = indexOf(params, ',');
            return ((index != -1 && index < lenght)
                && isRegistrator(substring(params, 0, index - 1))
                && isRegistrator(substring(params, index + 1, lenght)))
            ? 1 : 0;
        }

        return 0;
    } else if(stringEquals(instr, "zeros") || stringEquals(instr, "ones")
            || stringEquals(instr, "jal") || stringEquals(instr, "jr")) {

        char *params = removeAll(stringOffset(instruction, space), ' ');
        int lenght = strlen(params);

        return ((lenght == 2 || lenght == 3) && isRegistrator(params)) ? 1 : 0;
    } else if(stringEquals(instr, "loadlit") || stringEquals(instr, "lcl")
            || stringEquals(instr, "lch")) {
        return 1;
    } else if(stringEquals(instr, "j")) {
        return 1;
    } else if(startWith(instr, "jt.") || startWith(instr, "jf.")) {
        return 1;
    } else {
        return 0;
    }
}

//Verifica se uma instrução com label é válida
int isValidLabeled(char *instruction) {
    int twoPoints = indexOf(instruction, ':');
    //Se após os dois pontos há um espaço e ao menos um caractere
    if(strlen(instruction) > twoPoints+1+2 && instruction[twoPoints+1] == ' ') {
        return isLabel(substring(instruction, 0, twoPoints-1)) && isValidInstruction(stringOffset(instruction, twoPoints+2));}
    else return 0;
}

//Verifica se uma instrução é válida
int isValid(char *instruction) {
    //Se tiver dois pontos, só pode ser instrução com label
    if(indexOf(instruction, ':') > -1) return isValidLabeled(instruction);
    else return isValidInstruction(instruction);
}

/*  Percorre todas as linhas verificando as diretivas e se as instruções são válidas.
    Retorna uma 'lista' de instruções válidadas, sem as diretivas.*/
int getInstructions(Line *first) {
    //Verifica se o código assembly contém a diretiva .module
    if(!startWith(first->text, ".module ") || strlen(first->text) < 9) {
        printf("[ERRO] Um programa deve iniciar com \".module <NOME_DO_PROGRAMA>\"\n");
        return 0;
    } else {
        printf("[INFO] \".module\" encontrado: %s\n", stringOffset(first->text, 8));
    }

    Line *aux = first->next;

    while(aux != NULL) {
        if(stringEquals(aux->text, ".pseg")) {
            printf("[INFO] \".pseg\" encontrado.\n");
            aux = aux->next;
            while(aux != NULL && aux->text[0] != '.') {
                if(!isValid(aux->text)) {
                    printf("[ERRO] Erro encontrado na linha %d. Instrucao invalida: \"%s\"\n", aux->number, aux->text);
                    return 0;
                }
                aux = aux->next;
            }
        } else if(stringEquals(aux->text, ".dseg")) {
            printf("[INFO] \".dseg\" encontrado.\n");
            aux = aux->next;
            while(aux != NULL && (aux->text[0] != '.' || startWith(aux->text, ".word "))) {
                aux = aux->next;
            }
        } else if(stringEquals(aux->text, ".end")) {
            int lineNumber = aux->number;
            int lineCount = -1;
            Line *aux2 = aux;
            do {
                lineCount++;
                aux = aux->next;
            } while(aux != NULL);
            if(lineCount > 0) {
                printf("[WARN] \".end\" encontrado na linha %d, %d linha(s) ignorada(s) apos esta diretiva.\n", lineNumber, lineCount);
            } else {
                printf("[INFO] \".end\" encontrado.", lineNumber, lineCount);
            }
            aux = aux2;
            break;
        }
    }

    if(aux == NULL) {
        printf("[ERRO] A diretiva \".end\" nao foi encontrada. Ela deve estar no fim do programa.\n");
        return 0;
    }

    return 1;
}