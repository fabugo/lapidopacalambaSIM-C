#ifndef FORMATTER_H
#define FORMATTER_H

#include <stdio.h>
#include <string.h>
#include "reader.h"
#include "string.h"

struct INSTRUCTION {
    int address;
    char *content;
    struct INSTRUCTION *previous;
    struct INSTRUCTION *next;
};
typedef struct INSTRUCTION Instruction;

/*  Percorre todas as linhas verificando se as diretivas e instruções são válidas. E removendo
    espaços desnecessários. Retorna uma 'lista' de instruções validadas, sem as diretivas.*/
Instruction *formatInstructions(Line *first);

#endif