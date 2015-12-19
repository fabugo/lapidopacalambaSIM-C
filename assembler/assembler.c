#include <stdio.h>
#include <string.h>

#include "string.h"
#include "reader.h"
#include "formatter.h"

void mount(char *input) {
    printf("\n[INFO] Lendo o arquivo \"%s\"\n", input);
    Line *line = read(input);
    if(line != NULL) {
        printf("[INFO] Analisando o conteudo lido\n", input);
        if(formatInstructions(line) == 1)
            printf("\n[INFO] Montagem concluida com sucesso\n");
    }
    printf("-----------------------------------------------------------\n\n");
}

int main(int argc, char *argv[]) {
    int x;
    for(x = 1; x < argc; x++) {
        mount(argv[x]);
    }
}