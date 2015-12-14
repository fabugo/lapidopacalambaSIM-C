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

//Fun��o para ler uma linha do arquivo desconsiderando espacos excessivos e coment�rios de codigo
char *nextLine() {
    char *line = malloc(100 * sizeof(char));

    int x = 0;
    char c;
    while(!feof(inputFile)) { //Caso chegue ao fim do arquivo, a leitura e encerrada
        c = fgetc(inputFile);
        if(c=='\n') { //Se 'c' for o fim da linha, encerra a leitura dessa linha
            break;
        } else if(c==';') { //Se 'c' iniciar um comentario
            do { //Consome todos os caracteres seguintes a ";" ate o final do arquivo ou linha
                c = fgetc(inputFile);
            } while(feof(inputFile) == 0 && c != '\n');
            break; //Finaliza a leitura da linha
        } else if((c==' ' || c=='\t') ) { //Se 'c' for um espaco ou caractere de tabulacao.
            if((x==0 || (line[x-1]==' ')))
                //Caso seja o inicio da linha ou o ultimo caractere dela ja tenha sido um espaco, c sera ignorado
                continue;
            else //Tab ou espaco sera representado com espaco
                line[x++] = ' ';
        } else {
            line[x++] = c;
        }
    }
    if(x>0 && (line[x-1]==' ' || line[x-1]=='\t')) //Se o ultimo caractere for um espaco, ele sera removido
        x--;
    line[x] = '\0'; //Finaliza a linha
    return line;
}

//Fun��o para ler linha a linha do arquivo de caminho 'path' e armazenalas em estruturas do tipo Line
Line *readFile(char path[]) {
    inputFile = fopen(path, "r"); //Abre o arquivo 'path' apenas para leitura

    if(inputFile != NULL) { //Se o arquivo foi aberto com sucesso.
        Line *first = malloc(sizeof(Line)), *current = NULL;

        int lineCount = 0;
        while(!feof(inputFile)) { //Enquanto n�o chegar ao fim do arquivo
            char *text = nextLine();
            lineCount++;

            if(strlen(text) > 0) {
                if(current == NULL) { //Se for a primeira linha
                    first->number = lineCount;
                    first->text = text;
                    current = first; //'current' aponta para o mesmo Line de 'first'
                } else {
                    current->next = malloc(sizeof(Line)); //Aloca um novo espa�o para o pr�ximo Line
                    current->next->number = lineCount; //Atualiza o valor da linha com o incremento do valor corrente
                    current->next->text = text;
                    current->next->previous = current; //O ponteiro 'previous' do pr�ximo Line aponta para o Line corrente
                    current = current->next; //o Line corrente passa a ser o pr�ximo
                }
            }
        }
        return first;
    } else {
        printf("ERRO! Arquivo nao encontrado\n");
        return NULL;
    }
}
