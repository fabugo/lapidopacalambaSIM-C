#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//Retorna uma substring de 'str' a partir da posição 'start'.
char *strOffset(char *str, int start);

//Retorna uma substring de 'str' a partir da posição 'start' até a posição 'end'.
char *substring(char *str, int start, int end);

//Retorna a posição da primeira ocorrência do caractere 'c' na string 'str'.
int indexOf(char *str, char c);

//Retorna a posição da última ocorrência do caractere 'c' na string 'str'.
int lastIndexOf(char *str, char c);

//Retorna 1 se a string 'str' possui apenas caracteres de A-Z, a-z ou 0-9, ou 0, caso contrário.
int isAlphanumeric(char *str);

//Retorna 1 se a string 'str' representar um número inteiro, ou 0, caso contrário.
int isNumber(char *str);

//Retorna 1 se as strings 'str1' e 'str2' forem iguais ou 0, caso contrário.
int strEquals(char *str1, char* str2);

//Retorna 1 se a string 'str' iniciar com a string 'start' ou 0, caso contrário.
int startWith(char *str, char *start);

//Remove todos as ocorrencias de 'c' na string 'str' no intervalo entre as posições 'start' e 'end'.
void removeAll(char *str, int start, int end, char c);

//Troca todos as ocorrencias de 'replaced' na string 'str' por 'toReplace'.
char *replaceAll(char *str, char *replaced, char *toReplace);

//Retorna 1 se a string 'str1' conter 'str2' ou 0, caso contrário.
int contains(char *str1, char *str2);

//Retorna a string 'str' escrita na ordem inversa.
char *invert(char *str);

//Retorna uma string contendo a representação binária do valor 'value' com 'size' bits. Size pode ser 4, 16 ou 32.
char *decimalToBinary(char *value, int size);

//Retorna uma string contendo a representação decimal dos bits informado na string 'bits'.
long long int binaryToDecimal(char *bits, int width);
