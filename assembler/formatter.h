#ifndef FORMATTER_H
#define FORMATTER_H

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "string.h"

/*  Percorre todas as linhas verificando se as diretivas e instruções são válidas. E removendo
    espaços desnecessários. Retorna uma 'lista' de instruções validadas, sem as diretivas.*/
int formatInstructions(Line *line);

#endif
