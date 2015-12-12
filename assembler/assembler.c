#include <stdio.h>
#include "reader.h"

int main(int argc, char const *argv[]) {
    Line *line = readFile("input/teste1.asm");

    while(line != NULL) {
        printf("%s\n", line->text);
        line = line->next;
    }
}
