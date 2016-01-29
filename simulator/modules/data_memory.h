/*
	Representação da memória de dados
*/

#ifndef DATA_MEMORY_H
#define DATA_MEMORY_H

#include <string.h>

#include "../defs.h"
#include "../../lib/string.h"

struct DATA_MEMORY {
    char *input;			//WP: Ponteiro para o sinal de saída PRA do banco de registradores
    						//Dado a ser escrito
    char *address;			//AD: Ponteiro para o sinal de saída PRB do banco de registradores
    						//Endereço onde será executada a operação de leitura/escrita
    char output[33]; 		//PR: Dado lido
    
    char data[DM_SIZE][33]; //Matriz de tamanho 'DM_SIZE' para armazenar dados de 32 bits
};
typedef struct DATA_MEMORY DM;

extern DM dm;

/*
	Função que representa o sinal W_DM da unidade de controle. Se 'value' for 1, o conteúdo
	de 'input' será armazenado no endereço indicado por 'address'. Caso seja 0, o conteúdo
	do endereço 'address' será posto na saída.
*/
void W_DM(char value);

/*
	Função que reseta á memória de dados através do sinal RST_DM da unidade de controle.
	Se 'value' for 1, a saida assim como toda a memória de dados serão zeradas
*/
void RST_DM(char value);

#endif