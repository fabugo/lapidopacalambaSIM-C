#include <stdio.h>

#include "../string.h"
#include "reader.h"
#include "analyzer.h"

void mount(char *input) {
    printf("[INFO] Lendo o arquivo \"%s\"\n", input);
    Line *line = read(input);
    if(line != NULL) {
        printf("[INFO] Analisando o conteudo lido\n", input);
        if(getInstructions(line) == 1)
            printf("\n[INFO] Montagem concluida com sucesso\n");
    }
    printf("----------------------------------------\n\n\n");
}

int main(int argc, char const *argv[]) {
    /*Line *line = read("input/binary.asm");
    while(line != NULL) {
        printf("%d -  %s\n", line->number, line->text);
        line = line->next;
    }*/

    mount("input/teste.asm");
    mount("input/binary search.asm");
    mount("input/bubble sort.asm");
    mount("input/fibonacci.asm");
    mount("input/teste1.asm");
    mount("input/teste2.asm");
    mount("input/teste3.asm");
}
