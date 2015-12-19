#include "formatter.h"

int validate(char *instr);

int validateLabeled(char *instr);

int validateClean(char *instr);

int isRegistrator(char *str);

int isConstant(char *str, int size);

int isLabel(char *str);

int formatInstructions(Line *first) {
    if(!startWith(first->text, ".module ") || strlen(first->text) < 9) {
        printf("[ERRO] Um programa deve iniciar com \".module <NOME_DO_PROGRAMA>\"\n");
        return 0;
    } else {
        printf("[INFO] \".module\" encontrado: %s\n", strOffset(first->text, 8));
    }

    Line *aux = first->next;

    while(aux != NULL) {
        if(strEquals(aux->text, ".pseg")) {
            printf("[INFO] \".pseg\" encontrado.\n");
            aux = aux->next;
            while(aux != NULL && aux->text[0] != '.') {
                if(!validate(aux->text)) {
                    printf("[ERRO] Erro encontrado na linha %d. Instrucao invalida: \"%s\"\n", aux->number, aux->text);
                    return 0;
                }
                aux = aux->next;
            }
        } else if(strEquals(aux->text, ".dseg")) {
            printf("[INFO] \".dseg\" encontrado.\n");
            aux = aux->next;
            while(aux != NULL) {
                int twoPoints = indexOf(aux->text, ':');
                if(twoPoints > -1) {
                    if(isLabel(substring(aux->text, 0, twoPoints - 1))) {
                        int lenght = strlen(aux->text);
                        if(lenght > twoPoints+1 && aux->text[twoPoints+1] == ' ' && lenght > twoPoints+2) {
                            Line *temp = malloc(sizeof(Line));
                            temp->number = aux->number;
                            temp->text = strOffset(aux->text, twoPoints+2);
                            temp->next = aux->next;
                            temp->previous = aux;
                            aux->next->previous = temp;
                            aux->next = temp;
                        }

                        aux = aux->next;
                        while(startWith(aux->text, ".word ")) {
                            if(!isConstant(strOffset(aux->text, 7), 32)) {
                                printf("[ERRO] Erro encontrado na linha %d. Instrucao invalida: \"%s\"\n", aux->number, aux->text);
                                return 0;
                            }
                            aux = aux->next;
                        }
                    } else {
                        printf("[ERRO] Erro encontrado na linha %d. Instrucao invalida: \"%s\"\n", aux->number, aux->text);
                        return 0;
                    }
                } else if(strEquals(aux->text, ".end")) {
                    break;
                } else {
                    printf("[ERRO] Erro encontrado na linha %d. Instrucao invalida: \"%s\"\n", aux->number, aux->text);
                    return 0;
                }
            }
        } else if(strEquals(aux->text, ".end")) {
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

int validate(char *instr) {
    if(indexOf(instr, ':') > -1)
        return validateLabeled(instr);
    else
        return validateClean(instr);
}

int validateLabeled(char *instr) {
    int twoPoints = indexOf(instr, ':');

    if(strlen(instr) > twoPoints+1+2 && instr[twoPoints+1] == ' ')
        return isLabel(substring(instr, 0, twoPoints-1)) && validateClean(strOffset(instr, twoPoints+2));
    else
        return 0;
}

int validateClean(char *instr) {
    int space = indexOf(instr, ' ');
    if(space == -1) {
        return strEquals(instr, "nop") ? 1 : 0;
    }

    //Instruções com três registradorers
    if(startWith(instr, "add ") || startWith(instr, "addinc ") || startWith(instr, "subdec ")
            || startWith(instr, "sub ") || startWith(instr, "and ") || startWith(instr, "andnota ")
            || startWith(instr, "andnotb ") || startWith(instr, "xor ") || startWith(instr, "or ")
            || startWith(instr, "nand ") || startWith(instr, "xnor ") || startWith(instr, "ornata ")
            || startWith(instr, "ornotb ")) {

        removeAll(instr, space + 1, strlen(instr), ' ');
        char *params = strOffset(instr, space + 1);
        int lenght = strlen(params);

        if(lenght >= 8 && lenght <= 11) {
            int firstIndex = indexOf(params, ',');
            int lastIndex = lastIndexOf(params, ',');
            return ((firstIndex != -1 && lastIndex != -1 && firstIndex != lastIndex)
                && isRegistrator(substring(params, 0, firstIndex - 1))
                && isRegistrator(substring(params, firstIndex + 1, lastIndex - 1))
                && isRegistrator(substring(params, lastIndex + 1, lenght)))
            ? 1 : 0;
        }

        return 0;

    //Instruções com dois registradorers
    } else if(startWith(instr, "inca ") || startWith(instr, "deca ") || startWith(instr, "lsl ")
            || startWith(instr, "asr ") || startWith(instr, "passa ") || startWith(instr, "passb ")
            || startWith(instr, "passnota ") || startWith(instr, "passnotb ") || startWith(instr, "load ")
            || startWith(instr, "store ")) {

        removeAll(instr, space + 1, strlen(instr), ' ');
        char *params = strOffset(instr, space + 1);
        int lenght = strlen(params);

        if(lenght >= 5 && lenght <= 7) {
            int index = indexOf(params, ',');
            return ((index != -1)
                && isRegistrator(substring(params, 0, index - 1))
                && isRegistrator(substring(params, index + 1, lenght)))
            ? 1 : 0;
        }

        return 0;

    //Instruções com um registrador
    } else if(startWith(instr, "zeros") || startWith(instr, "ones") || startWith(instr, "jal")
            || startWith(instr, "jr")) {
        return isRegistrator(strOffset(instr, space + 1));

    //Instruções com um registrador e uma constante
    } else if(startWith(instr, "loadlit") || startWith(instr, "lcl") || startWith(instr, "lch")) {
        char *params = strOffset(instr, space + 1);
        int lenght = strlen(params);
        
        if(lenght >= 4) {
            int index = indexOf(params, ',');
            if(index != -1 && (index == 2 || index == 3)) {
                if(index+1 < lenght && params[index+1] == ' ') {
                    removeAll(params, 0, index+2, ' ');
                    index = indexOf(params, ',');
                }

                return (isRegistrator(substring(params, 0, index - 1))
                    && isConstant(substring(params, index + 1, lenght), 16));
            }
        }

        return 0;

    //Instruções j com apenas um label
    } else if(startWith(instr, "j")) {
        return (strlen(instr) < 3) ? 0 : isLabel(strOffset(instr, space + 1));

    //Instruções de desvio com condição e label
    } else if(startWith(instr, "jt.") || startWith(instr, "jf.")) {
        char *cond = substring(instr, 3, space);
        if(strEquals(cond, "neg") || strEquals(cond, "zero") || strEquals(cond, "carry")
            || strEquals(cond, "negzero")|| strEquals(cond, "true") || strEquals(cond, "overflow")) {
            return isLabel(strOffset(instr, space + 1));
        }
        return 0;
    } else {
        return 0;
    }
}

int isRegistrator(char *str) {
    return (strEquals(str, "r0") || strEquals(str, "r1")
        || strEquals(str, "r2") || strEquals(str, "r3")
        || strEquals(str, "r4") || strEquals(str, "r5")
        || strEquals(str, "r6") || strEquals(str, "r7")
        || strEquals(str, "r8") || strEquals(str, "r9")
        || strEquals(str, "r10") || strEquals(str, "r11")
        || strEquals(str, "r12") || strEquals(str, "r13")
        || strEquals(str, "r14") || strEquals(str, "r14"))
    ? 1 : 0;
}

int isConstant(char *str, int size) {
    if(startWith(str, "LOWBYTE ") || startWith(str, "HIGHBYTE ")) {
        return isLabel(strOffset(str, indexOf(str, ' ') + 1));
    } else {
        int lenght = strlen(str);
        int x;

        return 1;

        for(x = 0; x < lenght; x++) {
            if(str[lenght] < '0' || str[lenght] > '9') {
                return 0;
            }
        }

        return 1;
    }
}

int isLabel(char *str) {
    return isAlphanumeric(str);
}