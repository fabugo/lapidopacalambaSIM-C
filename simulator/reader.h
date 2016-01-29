#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	INSTRUCTION_SIZE	33  //32 + 1 para o \0

//Estrutura utilizada para armazenar as informações de uma instrução, como seu conteúdo e endereço
struct INSTRUCTION {
    int address;                    //Endereço relativo da instrução
    char *content;                  //Conteúdo
    struct INSTRUCTION *previous;   //Instrução anterior
    struct INSTRUCTION *next;       //Próxima instrução
};
typedef struct INSTRUCTION Instr;

FILE *inputFile;

//Lê e retorna os próximos 32 caracteres (próxima instrução) do arquivo de entrada.
//Se chegar ao fim do arquivo, ela retora null
char *nextInstruction() {
    return fgets(malloc(INSTRUCTION_SIZE * sizeof(char)), INSTRUCTION_SIZE, inputFile);
}

//Função que lê um arquivo de entrada e retorna uma "lista" contendo todas as instruções
Instr *read(char path[]) {
    inputFile = fopen(path, "r");

    if(inputFile != NULL) { //Se o arquivo for aberto corretamente
        Instr *first = malloc(sizeof(Instr)), *current = NULL;

        int instrCount = 0; //Contagem utilizada para endereçar as instruções
        char *content;
        while((content = nextInstruction()) != NULL) { //Enquanto a leitura não chegar ao fim do arquivo
            if(strEquals(content, "\n")) continue; //Ignora o \n;
            if(current == NULL) { //Se for a primeira instrução lida
                //Cria a primeira estrutura 'Instr'
                first->address = instrCount;
                first->content = content;
                first->next = NULL;
                first->previous = NULL;
                current = first;
            } else {
                //A partir do elemento atual, ele cria o próximo, em seguida o torna o atual
                current->next = malloc(sizeof(Instr));
                current->next->address = instrCount;
                current->next->content = content;
                current->next->previous = current;
                current = current->next;
                current->next = NULL;
            }
            instrCount++;
        }

        fclose(inputFile);
        return first;
    } else {
        printf("[ERRO] Arquivo nao encontrado.\n");
        return NULL;
    }
}
