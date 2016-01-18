#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE    100 //Tamanho m�ximo da linha ignorando espa�os e coment�rios

/*	Estrutura usada para armazenar uma linha do arquivo, numerando-a e dando referencia
	para a proxima linha
*/
struct LINE {
    long long int number;
    char *text;
    struct LINE *next;
};
typedef struct LINE Line;

//Fun��o para ler linha a linha do arquivo de caminho 'path' e armazen�-las em estruturas do tipo Line
Line *read(char path[]);

#endif