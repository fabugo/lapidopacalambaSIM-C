#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura usada para armazenar uma linha do arquivo, numerando-a e dando referencia para a linha anterior e a proxima.
struct LINE {
    int number;
    char *text;
    struct LINE *previous;
    struct LINE *next;
};
typedef struct LINE Line;

FILE *inputFile;

//Função para ler a próxima linha do arquivo indicado por 'inputFile'
char *nextLine() {
    char *line = malloc(200 * sizeof(char));
    fgets(line, 200, inputFile);
    return line;
}

//Função para ler linha a linha do arquivo de caminho 'path' e armazenalas em estruturas do tipo Line
Line *readFile(char path[]) {
    inputFile = fopen(path, "r"); //Abre o arquivo 'path' apenas para leitura

    if(inputFile != NULL) { //Se o arquivo foi aberto com sucesso.
        Line *first = malloc(sizeof(Line)), *current = NULL;

        while(!feof(inputFile)) { //Enquanto não chegar ao fim do arquivo
            char *text = nextLine();

            if(strlen(text) > 0) {
                if(current == NULL) { //Se for a primeira linha
                    first->number = 1;
                    first->text = text;
                    current = first; //'current' aponta para o mesmo Line de 'first'
                } else {
                    current->next = malloc(sizeof(Line)); //Aloca um novo espaço para o próximo Line
                    current->next->number = current->number+1; //Atualiza o valor da linha com o incremento do valor corrente
                    current->next->text = text;
                    current->next->previous = current; //O ponteiro 'previous' do próximo Line aponta para o Line corrente
                    current = current->next; //o Line corrente passa a ser o próximo
                }
            }
        }
        return first;
    } else {
        printf("ERRO! Arquivo nao encontrado\n");
        return NULL;
    }
}
