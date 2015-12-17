#include <string.h>
#include <stdlib.h>

//Retorna uma substring de 'source' de tamanho 'size' a partir da posição 'offset'
char *create(char *source, int size, int offset) {
	char *output = malloc(size + 1);
	int x = 0;
	for(; x < size; x++) output[x] = source[x+offset];

	output[x] = '\0';
	return output;
}

//Retorna uma substring de 'str' a partir da posição 'start'
char *stringOffset(char *str, int start) {
	int lenght = strlen(str);
	int size = (lenght-start) > 0 ? lenght-start : 0;
	return create(str, size, start);
}

//Retorna uma substring de 'str' a partir da posição 'start' até a posição 'end'
char *substring(char *str, int start, int end) {
	int lenght = strlen(str);
	int size = (start >= 0 && (end - start) < lenght) ? end - start + 1 : 0;
	if(start >= 0 && start < lenght) {
		if((end - start) < lenght) size = end - start + 1;
		else size = lenght - start;
	} else {
		size = 0;
	}
	return create(str, size, start);
}

//Retorna a posição da primeira ocorrência do caractere 'c' na string 'str'
int indexOf(char *str, char c) {
	int lenght = strlen(str);
	int x;
	for(x = 0; x < lenght; x++) if(str[x] == c) return x;
	return -1;
}

//Retorna a posição da última ocorrência do caractere 'c' na string 'str'
int lastIndexOf(char *str, char c) {
	int lenght = strlen(str);
	int x;
	for(x = lenght-1; x >= 0; x--) if(str[x] == c) return x;
	return -1;
}

//Retorna 1 se a string 'str' possui apenas caracteres de A-Z, a-z ou 0-9, ou 0, caso contrário
int isAlphanumeric(char *str) {
	int lenght = strlen(str);
	int x;
	for(x = 0; x < lenght; x++) { //Percorre todo o label verificando se cada caractere é válido
        if((str[lenght] >= '0' || str[lenght] <= '9') && (str[lenght] >= 'A' && str[lenght] <= 'Z') || (str[lenght] >= 'a' && str[lenght] <= 'z')) {
            return 0;
        }
    }
    return 1;
}

//Retorna 1 se as strings 'str1' e 'str2' forem iguais ou 0, caso contrário
int stringEquals(char *str1, char* str2) {
    int lenght1 = strlen(str1);
    int lenght2 = strlen(str2);
	return (lenght1 == lenght2 && memcmp(str1, str2, lenght1) == 0) ? 1 : 0;
}

//Retorna 1 se a string 'str' iniciar com a string 'start' ou 0, caso contrário
int startWith(char *str, char *start) {
	return (memcmp(str, start, strlen(start)) == 0) ? 1 : 0;
}

//Retorna uma nova string criada a partir da string 'str', removendo todos os caracteres 'c'
char *removeAll(char *str, char c) {
	int lenght = strlen(str);
	int count = 0;
	int x;
	for(x = 0; x < lenght; x++) if(str[x] == c) count++;

	char *replaced = malloc(lenght - count + 1);
	int a;
	for(x = 0, a = 0; a <= (lenght - count); x++) {
		if(str[x] == c) {
			continue;
		}
		replaced[a] = str[x];
		a++;
	}
	replaced[a] == '\0';

	return replaced;
}