#include <string.h>

char *create(char *source, char *output, int size, int offset) {
	int x = 0;
	for(; x < size; x++) {
		output[x] = source[x+offset];
	}

	output[x] = '\0';
	return output;
}

char *stringOffset(char *string, int start) {
	int lenght = strlen(string);
	int size = (lenght-start) > 0 ? lenght-start : 0;
	return create(string, malloc((size + 1) * sizeof(char)), size, start);
}

char *substring(char *string, int start, int end) {
	int lenght = strlen(string);
	int size = (start >= 0 && (end - start) < lenght) ? end - start + 1 : 0;
	return create(string, malloc((size + 1) * sizeof(char)), size, start);
}
