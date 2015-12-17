#include <string.h>

// Cria uma substring de 'source' de tamanho 'size' a partir da posição 'offset'
char *create(char *source, int size, int offset) {
	char *output = malloc((size + 1) * sizeof(char));
	int x = 0;
	for(; x < size; x++) output[x] = source[x+offset];

	output[x] = '\0';
	return output;
}

//Cria uma substring de 'string' a partir da posição 'start'
char *stringOffset(char *string, int start) {
	int lenght = strlen(string);
	int size = (lenght-start) > 0 ? lenght-start : 0;
	return create(string, size, start);
}

//Cria uma substring de 'string' a partir da posição 'start' até a posição 'end'
char *substring(char *string, int start, int end) {
	int lenght = strlen(string);
	int size = (start >= 0 && (end - start) < lenght) ? end - start + 1 : 0;
	if(start >= 0 && start < lenght) {
		if((end - start) < lenght) size = end - start + 1;
		else size = lenght - start;
	} else {
		size = 0;
	}
	return create(string, size, start);
}

//Retorna a posição da primeira ocorrência do caractere 'c'
int indexOf(char *string, char c) {
	int lenght = strlen(string);
	int x;
	for(x = 0; x < lenght; x++) if(string[x] == c) return x;
	return -1;
}

//Retorna a posição da última ocorrência do caractere 'c'
int lastIndexOf(char *string, char c) {
	int lenght = strlen(string);
	int x;
	for(x = lenght-1; x >= 0; x--) if(string[x] == c) return x;
	return -1;
}

//Veririfica se o caractere 'c' é uma letra(não acentuada)/número ou não
int isAlphanumeric(char *string) {
	int lenght = strlen(string);
	int x;
	for(x = 0; x < lenght; x++) { //Percorre todo o label verificando se cada caractere é válido
        if((string[lenght] < '0' || string[lenght] > '9') && (string[lenght] < 'A' || string[lenght] > 'Z') && (string[lenght] < 'a' || string[lenght] > 'z')) {
            return 0;
        }
    }
    return 1;
}

//Verifica se duas strings são iguais
int stringEquals(char *string1, char* string2) {
    int lenght1 = strlen(string1);
    int lenght2 = strlen(string2);
	return (lenght1 == lenght2 && memcmp(string1, string2, lenght1) == 0) ? 1 : 0;
}

int startWith(char *string, char *start) {
	return (memcmp(string, start, strlen(start)) == 0) ? 1 : 0;
}

char *removeAll(char *string, char c) {
	int lenght = strlen(string);
	int count = 0;
	int x;
	for(x = 0; x < lenght; x++) if(string[x] == c) count++;

	char *replaced = malloc((lenght - count) * sizeof(char));
	int a;
	for(x = 0, a = 0; x < lenght; x++) if(string[x] != c) replaced[a++] = string[x];
	replaced[a] == '\0';

	return replaced;
}
