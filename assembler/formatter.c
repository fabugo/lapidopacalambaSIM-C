#include "formatter.h"

int validate(char *instruction);

int validateLabeled(char *instruction);

int validateClean(char *instruction);

int isRegistrator(char *str);

int isConstant(char *str);

int isLabel(char *str);

Instruction *formatInstructions(Line *first) {
    if(!startWith(first->text, ".module ") || strlen(first->text) < 9) {
        printf("[ERRO] Um programa deve iniciar com \".module <NOME_DO_PROGRAMA>\"\n");
        return NULL;
    } else {
        printf("[INFO] \".module\" encontrado: %s\n", stringOffset(first->text, 8));
    }

    Line *aux = first->next;

    while(aux != NULL) {
        if(stringEquals(aux->text, ".pseg")) {
            printf("[INFO] \".pseg\" encontrado.\n");
            aux = aux->next;
            while(aux != NULL && aux->text[0] != '.') {
                if(!validate(aux->text)) {
                    printf("[ERRO] Erro encontrado na linha %d. Instrucao invalida: \"%s\"\n", aux->number, aux->text);
                    return NULL;
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
        return NULL;
    }

    return malloc(sizeof(Instruction));
}

int validate(char *instruction) {
    if(indexOf(instruction, ':') > -1)
        return validateLabeled(instruction);
    else
        return validateClean(instruction);
}

int validateLabeled(char *instruction) {
    int twoPoints = indexOf(instruction, ':');

    if(strlen(instruction) > twoPoints+1+2 && instruction[twoPoints+1] == ' ')
        return isLabel(substring(instruction, 0, twoPoints-1)) && validateClean(stringOffset(instruction, twoPoints+2));
    else
        return 0;
}

int validateClean(char *instruction) {
    int space = indexOf(instruction, ' ');

    if(space == -1) {
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

int isRegistrator(char *str) {
    return (stringEquals(str, "r0") || stringEquals(str, "r1")
        || stringEquals(str, "r2") || stringEquals(str, "r3")
        || stringEquals(str, "r4") || stringEquals(str, "r5")
        || stringEquals(str, "r6") || stringEquals(str, "r7")
        || stringEquals(str, "r8") || stringEquals(str, "r9")
        || stringEquals(str, "r10") || stringEquals(str, "r11")
        || stringEquals(str, "r12") || stringEquals(str, "r13")
        || stringEquals(str, "r14") || stringEquals(str, "r14"))
    ? 1 : 0;
}

int isConstant(char *str) {
    int lenght = strlen(str);
    int x;

    for(x = 0; x < lenght; x++) {
        if(str[lenght] < '0' || str[lenght] > '9') {
            return 0;
        }
    }

    return 1;
}

int isLabel(char *str) {
    return isAlphanumeric(str);
}