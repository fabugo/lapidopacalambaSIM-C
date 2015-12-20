#include "reader.h"

FILE *inputFile;

//Função para ler uma linha do arquivo desconsiderando espacos excessivos e comentários de codigo.
char *nextLine();

Line *read(char path[]) {
    inputFile = fopen(path, "r"); //Abre o arquivo 'path' apenas para leitura

    if(inputFile != NULL && !feof(inputFile)) { //Se o arquivo foi aberto com sucesso
        Line *first = malloc(sizeof(Line)), *current = NULL;

        long long int lineCount = 0;
        while(!feof(inputFile)) { //Enquanto não chegar ao fim do arquivo
            char *text = nextLine();
            lineCount++;

            if(strlen(text) > 0) {
                if(current == NULL) { //Se for a primeira linha
                    //Cria a estrutura "Line" para armazenar as informações da primeira linha.
                    first->number = lineCount;
                    first->text = text;
                    first->next = NULL;
                    current = first;
                } else {
                     //A partir da linha corrente, é criada a próxima linha, que passará a ser a atual
                    current->next = malloc(sizeof(Line)); //Aloca um novo espaço para o próximo Line
                    current = current->next; //o Line corrente passa a ser o próximo
                    current->number = lineCount; //Atualiza o valor da linha com o incremento do valor corrente
                    current->text = text;
                    current->next = NULL;
                }
            }
        }

        fclose(inputFile);

        if(first->text == NULL) {
            printf("[R][ERRO] Arquivo vazio ou invalido\n");
            return NULL;
        }

        return first;
    } else if(inputFile == NULL) {
        printf("[R][ERRO] Arquivo nao encontrado\n");
    } else {
        fclose(inputFile);
        printf("[R][ERRO] Arquivo vazio ou invalido\n");
    }
    return NULL;
}

char *nextLine() {
    char *line = malloc(LINE_SIZE);

    int x = 0;
    char c;
    while(!feof(inputFile)) { //Caso chegue ao fim do arquivo, a leitura é encerrada
        c = fgetc(inputFile);
        if(c=='\n') { //Se 'c' for o fim da linha, encerra a leitura dessa linha
            break;
        } else if(c==';') { //Se 'c' iniciar um comentario
            do { //Consome todos os caracteres seguintes a ";" ate o final do arquivo ou linha
                c = fgetc(inputFile);
            } while(feof(inputFile) == 0 && c != '\n');
            break; //Finaliza a leitura da linha
        } else if((c==' ' || c=='\t') ) { //Se 'c' for um espaço ou caractere de tabulação
            if(x==0 || line[x-1]==' ' || line[x-1]==',')
                //Caso seja o inicio da linha ou o último caractere tenha sido um espaço ou uma virgula, c será ignorado
                continue;
            else //Tabulação ou espaço será representado com espaço
                line[x++] = ' ';
        } else {
            line[x++] = c;
        }
    }
    
    //Se o último caractere da string for um espaço, ele será removido
    if(x>0 && (line[x-1]==' ' || line[x-1]=='\t' || line[x-1]==-1)) x--;
    line[x] = '\0';
    return line;
}