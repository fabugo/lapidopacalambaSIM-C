#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define WINDOW_SIZE     25

void instruction(char* line) {
    printf("%s", line);
}

char* nextLine(FILE *file) {
    char line[9999] = "", buffer[WINDOW_SIZE];
    do {
        fgets(buffer, WINDOW_SIZE, file);
        strcat(line, buffer);
    } while(strchr(line, '\n') == NULL && feof(file) == 0);
    return line;
}

char* nextLine1(FILE *file) {
    char *line = (char*) malloc(0*sizeof(char)), buffer[WINDOW_SIZE];
    int temp = 1;
    do {
        fgets(buffer, WINDOW_SIZE, file);
        line = (char*)realloc(line, WINDOW_SIZE * temp * sizeof(char));
        temp++;
        strcat(line, buffer);
    } while(strchr(line, '\n') == NULL && feof(file) == 0);
    printf("%s", line);
    return line;
}

int readFile(const char* filePath) {
    FILE *input;
    input = fopen(filePath, "r");

    if(input != NULL) {
        while(!feof(input)) {
            instruction(nextLine(input));
        }
        return fclose(input);
    } else {
        printf("ERRO! Arquivo nao encontrado\n");
        return 1;
    }
}

int main(int argc, char const *argv[]) {
    int x;
    for(x = 1; x<argc; x++) {
        printf("%s: %s", argv[x], readFile(argv[x]) == 0
               ? "Success\n------------------------------------------------------------\n\n"
               : "Fail\n------------------------------------------------------------\n\n");
    }
}
