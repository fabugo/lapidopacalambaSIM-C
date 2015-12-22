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

char *strOffset(char *str, int start) {
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
        if(!isalnum(str[x]))
            return 0;
    }

    return 1;
}

int isNumber(char *str) {
	int lenght = strlen(str);
	if((lenght > 1 && (str[0] == '-' || str[0] == '+')) || lenght > 0) {
		int x;
		x = (str[0] == '-' || str[0] == '+') ? 1 : 0;

		for(; x < lenght; x++) {
			if(!isdigit(str[x]))
				return 0;
		}

		return 1;
	}

	return 0;
}

int strEquals(char *str1, char* str2) {
    int lenght1 = strlen(str1);
    int lenght2 = strlen(str2);

	return (lenght1 == lenght2 && memcmp(str1, str2, lenght1) == 0) ? 1 : 0;
}

int startWith(char *str, char *start) {
	return (memcmp(str, start, strlen(start)) == 0) ? 1 : 0;
}

void removeAll(char *str, int start, int end, char c) {
    int lenght = strlen(str);
    if(start >= 0 && start < lenght && end <= lenght && start < end) {
    	int x, y;
	    for(x = start; x < end; x++) {
	        if(str[x] == c) {
	            for(y = x; y < lenght-1; y++)
	                str[y] = str[y+1];
	            str[y] = '\0';
	            lenght--;
	            end--;
	        }
	    }
    }
}
char *replaceAll(char *str, char *replaced, char *toReplace) {
	int lenght = strlen(str);
	int rLenght = strlen(replaced);
	int tLenght = strlen(toReplace);
	int x, y, z;
	char *newStr = malloc(lenght+1);
	strcpy(newStr, str);

    for(x = 0; x <= lenght-rLenght; x++) {
    	if(startWith(strOffset(newStr, x), replaced)) {
    		if(tLenght == rLenght) {
				for(y = x, z = 0; z < tLenght; z++, y++)
					newStr[y] = toReplace[z];
			} else if(tLenght > rLenght) {
    			int nlenght = lenght + (tLenght - rLenght);
    			newStr = realloc(newStr, nlenght+1);
        		for(y = lenght-1, z = nlenght-1; y >= (x+rLenght); y--, z--) {
        			newStr[z] = newStr[y];
        		}

            	for(y = x, z = 0; z < tLenght; z++, y++) {
					newStr[y] = toReplace[z];
            	}

        		newStr[nlenght] = '\0';
			} else {
				for(y = x, z = 0; z < tLenght; z++, y++)
					newStr[y] = toReplace[z];
				for(;y < lenght; y++)
					newStr[y] = newStr[y+ rLenght - tLenght];
				for(; y < lenght; y++)
					newStr[y] = toReplace[y+1];
				lenght -= rLenght - tLenght;
				newStr[y] = '\0';
			}
        }
    }

    return newStr;
}

int contains(char *str1, char *str2) {
	int lenght = strlen(str1);
	int rLenght = strlen(str2);
	int x;
    for(x = 0; x <= lenght-rLenght; x++) {
    	if(startWith(strOffset(str1, x), str2))
    		return 1;
    }
    return 0;
}

char *invert(char *str) {
	int lenght = strlen(str);
	char *out = malloc(lenght+1);
	int x;

	for(x = 0; x < lenght-1; x++) {
		out[x] = str[lenght-x-1];
	}
	out[x] = '\0';

	return out;
}

char *decimalToBinary(char *value, int size) {
    long long int v = atoll(value);
    char *temp = malloc(size+1);
    int x;

    if(size == 4) {
        for(x=0; x<size; x++) {
            if((v & 0x8) !=0) temp[x] = '1';
            else temp[x] = '0';
            v = v<<1;
        }
    } else if(size == 16) {
        for(x=0; x<size; x++) {
            if((v & 0x8000) !=0) temp[x] = '1';
            else temp[x] = '0';
            v = v<<1;
        }
    } else {
        for(x=0; x<size; x++) {
            if((v & 0x80000000) !=0) temp[x] = '1';
            else temp[x] = '0';
            v = v<<1;
        }
    }
    temp[x] = '\0';

    return temp;
}

//conversor binario para decimal lli
int ctoi(char c){
    if(c == 49)
        return 1;
    if(c == 48)
        return 0;
}
int ctoia(char c){
    if(c == 49)
        return 0;
    if(c == 48)
        return 1;
}
long long int binaryToDecimal(char *bin, int singned) {
	long long int 	dec,		mult;
    				dec = 0;    mult = 1;
    int width = strlen(bin)-1;
    for(width;width>=0;width--){
		if(singned)//se quiser retornar valor tanto negativo quanto positivo
	        if(ctoi(bin[0]))
	            dec +=(ctoia(bin[width])*mult);
	        else
	            dec +=(ctoi(bin[width])*mult);
		else//se quiser retornar apenas valores positivos
			dec +=(ctoi(bin[width])*mult);
        mult = mult * 2;
    }
    if(ctoi(bin[0]))
        dec = ~dec;
	return dec;
}
