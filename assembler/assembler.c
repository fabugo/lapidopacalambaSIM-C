#include <stdio.h>
#include <string.h>

#include "string.h"
#include "reader.h"
#include "formatter.h"
#include "checker.h"

struct INSTRUCTION {
    int address;
    char *content;
    struct INSTRUCTION *next;
};
typedef struct INSTRUCTION Instruction;

void start(char *input);

int mount(Line *line);

void createPseg(Line *line);

void createDseg(Line *line);

int main(int argc, char *argv[]) {
    int x;
    for(x = 1; x < argc; x++) {
        start(argv[x]);
    }
}

void start(char *input) {
    printf("\n[A][INFO] Lendo o arquivo \"%s\"\n", input);
    Line *line = read(input);
    if(line != NULL) {
        printf("[A][INFO] Analisando o conteudo lido\n");
        if(formatInstructions(line) == 1) {
            printf("[A][INFO] Verificando Labels\n");
            if(check(line) == 1)
                if(mount(line) == 1)
                    printf("\n[A][INFO] Montagem concluida com sucesso\n");
        }
    }
    printf("-----------------------------------------------------------\n\n");
}

Label *jumpers = NULL, *variables = NULL;
Instruction *psegInstr = NULL, *dsegInstr = NULL;

int mount(Line *line) {
    Line *aux = line;
    while((aux = aux->next) != NULL && (psegInstr == NULL || dsegInstr == NULL)) {
        if(strEquals(aux->text, ".pseg"))
            createPseg(aux);
        if(strEquals(aux->text, ".dseg"))
            createDseg(aux);
    }

    printf("\n->JUMPERS:\n");
    while(jumpers != NULL) {
        printf("%4.d  -  %s\n", jumpers->address, jumpers->text);
        jumpers = jumpers->next;
    }
    printf("\n");

    printf("\n->PSEG:\n");
    while(psegInstr != NULL) {
        printf("%4.d  -  %s\n", psegInstr->address, psegInstr->content);
        psegInstr = psegInstr->next;
    }
    printf("\n");

    printf("\n->VARIABLES:\n");
    while(variables != NULL) {
        printf("%4.d  -  %s\n", variables->address, variables->text);
        variables = variables->next;
    }
    printf("\n");

    printf("\n->DSEG:\n");
    while(dsegInstr != NULL) {
        printf("%4.d  -  %s\n", dsegInstr->address, dsegInstr->content);
        dsegInstr = dsegInstr->next;
    }
    printf("\n");

    return 1;
}

void createPseg(Line *line) {
    int addressCount = 0;
    Instruction *tempInstr = NULL;
    Label *tempLabel = NULL;

    while((line = line->next) != NULL && line->text[0] != '.') {
        char *content;
        int index = indexOf(line->text, ':');
        if(index > -1) {
            if(tempLabel == NULL) {
                jumpers = malloc(sizeof(Label));
                jumpers->address = addressCount;
                jumpers->text = substring(line->text, 0, index-1);
                jumpers->next = NULL;
                tempLabel = jumpers;
            } else {
                tempLabel->next = malloc(sizeof(Label));
                tempLabel = tempLabel->next;
                tempLabel->address = addressCount;
                tempLabel->text = substring(line->text, 0, index-1);
                tempLabel->next = NULL;
            }
            content = strOffset(line->text, index+2);
        } else {
            content = line->text;
        }

        if(tempInstr == NULL) {
            psegInstr = malloc(sizeof(Instruction));
            psegInstr->address = addressCount++;
            psegInstr->content = content;
            psegInstr->next = NULL;
            tempInstr = psegInstr;
        } else {
            tempInstr->next = malloc(sizeof(Instruction));
            tempInstr = tempInstr->next;
            tempInstr->address = addressCount++;
            tempInstr->content = content;
            tempInstr->next = NULL;
        }
    }
}

void createDseg(Line *line) {
    int instructionAddress = 0, memoryAddress = 0;
    Instruction *tempInstr = NULL;
    Label *tempLabel = NULL;

    //CONSTRUIR AS INSTRUÇÔES PARA O DSEG,
    //VERIFICAR ARRAY E VARIAVEL NA MESMA LINHA, INDO COMO ARRAY

    line = line->next;
    while(line != NULL && line->text[0] != '.') {
        if(tempLabel == NULL) {
            variables = malloc(sizeof(Label));
            variables->address = memoryAddress;
            variables->text = substring(line->text, 0, strlen(line->text)-2);
            variables->next = NULL;
            tempLabel = variables;
        } else {
            tempLabel->next = malloc(sizeof(Label));
            tempLabel = tempLabel->next;
            tempLabel->address = memoryAddress;
            tempLabel->text = substring(line->text, 0, strlen(line->text)-2);
            tempLabel->next = NULL;
        }

        while(startWith((line = line->next)->text, ".word")) {
            if(tempInstr == NULL) {
                dsegInstr = malloc(sizeof(Instruction));
                dsegInstr->address = instructionAddress++;
                dsegInstr->content = "loadlit r0,";//+temp;
                tempInstr = dsegInstr;
            } else {
                tempInstr->next = malloc(sizeof(Instruction));
                tempInstr = tempInstr->next;
                tempInstr->address = instructionAddress++;
                tempInstr->content = "loadlit r0,";//+temp;
            }

            tempInstr->next = malloc(sizeof(Instruction));
            tempInstr = tempInstr->next;
            tempInstr->address = instructionAddress++;
            tempInstr->content = "store 0, r0";
            tempInstr->next = NULL;
            memoryAddress++;
        }

        if(tempLabel->address == memoryAddress) {
            memoryAddress++;
        }
    }
}