#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE    100 //Tamanho máximo da linha ignorando espaços e comentários

/*	Estrutura usada para armazenar uma linha do arquivo, numerando-a e dando referencia
	para a proxima linha
*/
struct LINE {
    long long int number;
    char *text;
    struct LINE *next;
};
typedef struct LINE Line;

//Função para ler linha a linha do arquivo de caminho 'path' e armazená-las em estruturas do tipo Line
Line *read(char path[]);

#endif