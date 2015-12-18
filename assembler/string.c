#include "string.h"

//Retorna uma substring de 'source' de tamanho 'size' até iniciando da posição 'offset'.
char *create(char *source, int size, int offset) {
	char *output = malloc(size + 1);
	int x = 0;

	for(; x < size; x++)
		output[x] = source[x+offset];
	output[x] = '\0';

	return output;
}

char *stringOffset(char *str, int start) {
	int lenght = strlen(str);
	int size = (lenght-start) > 0 ? lenght-start : 0;

	return create(str, size, start);
}

char *substring(char *str, int start, int end) {
	int lenght = strlen(str);
	//Se o intervalo 'end'-'start' for inválido, o 'size' será 0
	int size = (start >= 0 && (end - start) < lenght) ? end - start + 1 : 0;
	
	if(start >= 0 && start < lenght) {
		if((end - start) < lenght)
			size = end - start + 1;
		else 
			size = lenght - start;
	} else {
		size = 0;
	}

	return create(str, size, start);
}

int indexOf(char *str, char c) {
	int lenght = strlen(str);
	int x;

	for(x = 0; x < lenght; x++)
		if(str[x] == c) return x;

	return -1;
}

int lastIndexOf(char *str, char c) {
	int lenght = strlen(str);
	int x;

	for(x = lenght-1; x >= 0; x--)
		if(str[x] == c)
			return x;

	return -1;
}

int isAlphanumeric(char *str) {
	int lenght = strlen(str);
	int x;

	for(x = 0; x < lenght; x++) {
        if((str[lenght] >= '0' || str[lenght] <= '9') && (str[lenght] >= 'A' && str[lenght] <= 'Z') || (str[lenght] >= 'a' && str[lenght] <= 'z')) {
            return 0;
        }
    }

    return 1;
}

int stringEquals(char *str1, char* str2) {
    int lenght1 = strlen(str1);
    int lenght2 = strlen(str2);

	return (lenght1 == lenght2 && memcmp(str1, str2, lenght1) == 0) ? 1 : 0;
}

int startWith(char *str, char *start) {
	return (memcmp(str, start, strlen(start)) == 0) ? 1 : 0;
}

char *removeAll(char *str, char c) {
	int lenght = strlen(str);
	int count = 0;
	int x;

	//Conta quantas ocorrencias de 'c' há na string 'str'
	for(x = 0; x < lenght; x++)
		if(str[x] == c)
			count++;

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