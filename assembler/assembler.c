#include <stdio.h>
#include <string.h>

#include "string.h"
#include "reader.h"
#include "formatter.h"

void mount(char *input);

int main(int argc, char *argv[]) {
    int x;
    for(x = 1; x < argc; x++) {
        mount(argv[x]);
    }
}

void mount(char *input) {
    printf("\n[A][INFO] Lendo o arquivo \"%s\"\n", input);
    Line *line = read(input);
    if(line != NULL) {
        printf("[A][INFO] Analisando o conteudo lido\n");
        if(formatInstructions(line) == 1) {
            printf("[A][INFO] Verificando Labels\n");
            if(check(line) == 1)
                printf("\n[A][INFO] Montagem concluida com sucesso\n");
        }
    }
    printf("-----------------------------------------------------------\n\n");
}