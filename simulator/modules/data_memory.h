/*
	Representação da memória de dados
*/

#ifndef DATA_MEMORY_H
#define DATA_MEMORY_H

#include <string.h>
#include "../defs.h"
#include "../../lib/string.h"

#include "register_bank.h"

struct DATA_MEMORY {
    char *input;	//Dado a ser escrito
    char *address;	//Endereço da posição de memória onde será feita a operação
    char output[33]; //Dado lido
    char data[DM_SIZE][33]; //Matriz de tamanho 'DM_SIZE' para armazenar dados de 32 bits
};
typedef struct DATA_MEMORY DM;

extern DM dm;

void DM_start();

/*
	Função que representa o sinal W_DM da unidade de controle. Se 'value' for 1, o conteúdo
	de 'input' será armazenado no endereço indicado por 'address'. Caso seja 0, o conteúdo
	do endereço 'address' será posto na saída.
*/
void W_DM(int value);

/*
	Função que reseta á memória de dados através do sinal RST_DM da unidade de controle.
	Se 'value' for 1, a saida assim como toda a memória de dados serão zeradas
*/
void RST_DM(int value);

#endif