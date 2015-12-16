#include <stdio.h>
#include <string.h>

//#include "reader.h"

int analyzer(Line *first) {
    if(memcmp(".module", first->text, 7)) {
        printf("[ERRO] Um programa deve iniciar com \".module <NOME_DO_PROGRAMA>\"\n");
        return 0;
    }

    Line *aux = first->next;
    Line *pseg, *dseg;

    while(!(aux == NULL || strcmp(aux->text, ".end") == 0)) {
        if(strcmp(aux->text, ".pseg") == 0) {
            aux = aux->next;
            while(aux != NULL && aux->text[0] != '.') {
                aux = aux->next;
            }
        } else if(strcmp(aux->text, ".dseg") == 0) {
            aux = aux->next;
            while(aux != NULL && (aux->text[0] != '.' || !memcmp(".word", first->text, 5))) {
                aux = aux->next;
            }
        } else {
            aux = aux->next;
        }
    }
    if(aux == NULL) {
        printf("[ERRO] A diretiva \".end\" nao foi encontrada. Ela deve estar no fim do programa.\n");
        return 0;
    } else {
        int lineNumber = aux->number;
        int lineCount = -1;
        do {
            lineCount++;
            aux = aux->next;
        } while(aux != NULL);
        if(lineCount > 0) {
            printf("[WARN] \".end\" encontrado na linha %d, %d linhas ignoradas apos esta diretiva.\n", lineNumber, lineCount);
        }
    }

    return 1;
}
