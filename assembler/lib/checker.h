#ifndef CHECKER_H
#define CHECKER_H

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "../../lib/string.h"

struct LABEL {
	long long int address;
    char *name;
    struct LABEL *next;
};
typedef struct LABEL Label;

/*
	Percorre as linhas de instruções verificando se os Labels de jumpers e variáveis utilizados em
	instruções foram declarados corretamente.
*/
int check(Line *line);

#endif