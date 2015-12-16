#include <string.h>

// Cria uma substring de 'source' de tamanho 'size' a partir da posição 'offset'
char *create(char *source, int size, int offset) {
	char *output = malloc((size + 1) * sizeof(char));
	int x = 0;
	for(; x < size; x++) {
		output[x] = source[x+offset];
	}

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
	return create(string, size, start);
}

//Retorna a posição da primeira ocorrência do caractere 'c'
int indexOf(char *string, char c) {
	int lenght = strlen(string);
	int x;
	for(x = 0; x < lenght; x++) {
		if(string[x] == c) {
			return x;
		}
	}

	return -1;
}

//Veririfica se o caractere 'c' é uma letra(não acentuada)/número ou não
int isAlphanumeric(char c) {
	int value = c;
	return (value >= 48 && value <= 57) || (value >= 65 && value <=90) || (value >= 97 && value <=122);
}
