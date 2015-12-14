#include <stdio.h>
#include "reader.h"

int main(int argc, char const *argv[]) {
    Line *line = readFile("input/teste1.asm");

    //Analyzer
    while(line != NULL) {
        printf("%d -   %s\n", line->number, line->text);
        line = line->next;
    }
}
