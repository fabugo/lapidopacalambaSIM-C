#include <stdio.h>
#include <string.h>

//#include "reader.h"

int analyzer(Line *first) {
    if(first == NULL) {
        printf("+++ EIIITA, esse arquivo ta escrito em papel branco com tinta transparente, tem nada p ser lido aqui n\n");
        return 0;
    }

    if(memcmp(".module", first->text, 7)) {
        printf("+++ Da um titulo p esse negocio, tente \".module <NOME_DO_PROGRAMA>\"\n");
        return 0;
    }

    Line *aux = first->next;
    Line *pseg, *dseg;

    while(aux != NULL) {
        if(aux->text[0] != '.' || (strcmp(aux->text, ".pseg") != 0 && strcmp(aux->text, ".dseg") != 0)) {
            printf("+++ O que e isso na linha %d \"%s\"? Acho que ta errado\n", aux->number, aux->text);
            return 0;
        }

        if(strcmp(aux->text, ".pseg") == 0) {
            aux = aux->next;

            while(aux != NULL && aux->text[0] != '.') {
                aux = aux->next;
            }
        } else { //.dseg
            aux = aux->next;

            while(aux != NULL && (aux->text[0] != '.' || memcmp(".word", first->text, 5))) {
                aux = aux->next;
            }
        }
    }

    return 1;
}
