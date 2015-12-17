#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE    100 //Tamanho máximo da linha ignorando espaços e comentários


//Estrutura usada para armazenar uma linha do arquivo, numerando-a e dando referencia para a linha anterior e a proxima.
struct LINE {
    int number;
    char *text;
    struct LINE *previous;
    struct LINE *next;
};
typedef struct LINE Line;

FILE *inputFile;

//Função para ler uma linha do arquivo desconsiderando espacos excessivos e comentários de codigo
char *nextLine() {
    char *line = malloc(LINE_SIZE * sizeof(char));

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
    
    //Se o ultimo caractere for um espaco, ele sera removido
    if(x>0 && (line[x-1]==' ' || line[x-1]=='\t' || line[x-1]==-1)) x--;
    line[x] = '\0'; //Finaliza a linha
    return line;
}

//Função para ler linha a linha do arquivo de caminho 'path' e armazenalas em estruturas do tipo Line
Line *read(char path[]) {
    inputFile = fopen(path, "r"); //Abre o arquivo 'path' apenas para leitura

    if(inputFile != NULL && !feof(inputFile)) { //Se o arquivo foi aberto com sucesso
        Line *first = malloc(sizeof(Line)), *current = NULL;

        int lineCount = 0;
        while(!feof(inputFile)) { //Enquanto não chegar ao fim do arquivo
            char *text = nextLine();
            lineCount++;

            if(strlen(text) > 0) {
                if(current == NULL) { //Se for a primeira linha
                    //Cria a estrutura "Line" para armazenar as informações da primeira linha.
                    first->number = lineCount;
                    first->text = text;
                    first->next = NULL;
                    first->previous = NULL;
                    current = first;
                } else {
                     //A partir da linha corrente, é criada a próxima linha, que passará a ser a atual
                    current->next = malloc(sizeof(Line)); //Aloca um novo espaço para o próximo Line
                    current->next->number = lineCount; //Atualiza o valor da linha com o incremento do valor corrente
                    current->next->text = text;
                    current->next->next = NULL;
                    current->next->previous = current; //O ponteiro 'previous' do próximo Line aponta para o Line corrente
                    current = current->next; //o Line corrente passa a ser o próximo
                }
            }
        }

        fclose(inputFile);

        if(first->text == NULL) {
            printf("[ERRO] Arquivo vazio ou invalido.\n");
            return NULL;
        }

        return first;
    } else if(inputFile == NULL) {
        printf("[ERRO] Arquivo nao encontrado.\n");
    } else {
        fclose(inputFile);
        printf("[ERRO] Arquivo vazio ou invalido.\n");
    }
    return NULL;
}
