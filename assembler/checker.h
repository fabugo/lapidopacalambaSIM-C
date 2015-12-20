#ifndef CHECKER_H
#define CHECKER_H

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "string.h"

struct LABEL {
	int address;
    char *text;
    struct LABEL *next;
};
typedef struct LABEL Label;

int check(Line *line);

#endif