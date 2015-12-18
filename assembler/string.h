#include <string.h>
#include <stdlib.h>

//Retorna uma substring de 'str' a partir da posição 'start'.
char *stringOffset(char *str, int start);

//Retorna uma substring de 'str' a partir da posição 'start' até a posição 'end'.
char *substring(char *str, int start, int end);

//Retorna a posição da primeira ocorrência do caractere 'c' na string 'str'.
int indexOf(char *str, char c);

//Retorna a posição da última ocorrência do caractere 'c' na string 'str'.
int lastIndexOf(char *str, char c);

//Retorna 1 se a string 'str' possui apenas caracteres de A-Z, a-z ou 0-9, ou 0, caso contrário.
int isAlphanumeric(char *str);

//Retorna 1 se as strings 'str1' e 'str2' forem iguais ou 0, caso contrário.
int stringEquals(char *str1, char* str2);

//Retorna 1 se a string 'str' iniciar com a string 'start' ou 0, caso contrário.
int startWith(char *str, char *start);

//Retorna uma nova string criada a partir da string 'str', removendo todos os caracteres 'c'.
char *removeAll(char *str, char c);