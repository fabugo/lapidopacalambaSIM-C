#include <stdio.h>
#include <string.h>

struct INSTRUCTION {
    int address;
    char *content;
    struct INSTRUCTION *previous;
    struct INSTRUCTION *next;
};
typedef struct INSTRUCTION Instruction;

//Verifica se uma instrução é válida de acordo com o ISA
int isValidInstruction(char *instruction) {
    return 1;
}

//Verifica se uma instrução com label é válida
int isValidLabeled(char *instruction) {
    int twoPoints = indexOf(instruction, ':');
    if(strlen(instruction) > twoPoints+1+2 && instruction[twoPoints+1] == ' ') {
        //Se após os dois pontos há um espaço e ao menos um caractere
        int validLabel = 1; //"Inoscente até que se prove o contrário"
        int x;
        for(x = 0; x < twoPoints; x++) { //Percorre todo o label verificando se cada caractere é válido
            if(!isAlphanumeric(instruction[x])) {
                validLabel = 0;
                break;
            }
        }

        //Se o label e a instrução após ele são válidos
        return validLabel && isValidInstruction(stringOffset(instruction, twoPoints+2));
    } else {
        return 0;
    }
}

//Verifica se uma instrução é válida
int isValid(char *instruction) {
    if(indexOf(instruction, ':') > -1) { //Se tiver dois pontos, só pode ser instrução com label
        return isValidLabeled(instruction);
    } else {
        return isValidInstruction(instruction);
    }
}

/*  Percorre todas as linhas verificando as diretivas e se as instruções são válidas.
    Retorna uma 'lista' de instruções válidadas, sem as diretivas.*/
int getInstructions(Line *first) {
    //Verifica se o código assembly contém a diretiva .module
    if(memcmp(".module ", first->text, 7) || strlen(first->text) < 9) {
        printf("[ERRO] Um programa deve iniciar com \".module <NOME_DO_PROGRAMA>\"\n");
        return 0;
    } else {
        printf("[INFO] \".module\" encontrado: %s\n", stringOffset(first->text, 8));
    }

    Line *aux = first->next;
    Line *pseg, *dseg;

    while(aux != NULL) {
        if(strcmp(aux->text, ".pseg") == 0) {
            printf("[INFO] \".pseg\" encontrado.\n");
            aux = aux->next;
            while(aux != NULL && aux->text[0] != '.') {
                if(!isValid(aux->text)) {
                    printf("[ERRO] Erro encontrado na linha %d. Instrucao invalida: \"%s\"\n", aux->number, aux->text);
                    return 0;
                }
                aux = aux->next;
            }
        } else if(strcmp(aux->text, ".dseg") == 0) {
            printf("[INFO] \".dseg\" encontrado.\n");
            aux = aux->next;
            while(aux != NULL && (aux->text[0] != '.' || memcmp(".word", aux->text, 5) == 0)) {
                aux = aux->next;
            }
        } else if(memcmp(".end", aux->text, 4) == 0) {
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