#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[]) {
    FILE *file;             //ponteiro do arquivo a ser manipulado
    char instruction[10],   //instrucao do programa
                par1[10],   //1 argumento do programa
                par2[10],   //2 argumento do programa
                par3[10],   //3 argumento do programa
                bin [32];   //saida do sistema

    int args,               //numero total de argumentos que a instrucao tem
        type;               //1 operacoes logicas
                            //2 operacoes aritmeticas
                            //3 operacoes com constantes
                            //4 operacoes de memoria
                            //5 operacoes de desvios
    char * pchr;            //ponteiro que auxilia contagem de argumentos
    char zero = '0';
    int i = 0;
    for(i;i<=31;i++){
        printf("%s\n",bin);
        fflush(stdin);
        bin[i] = NULL;
        bin[i] = zero;
    }

    //iniciando leitura
    file = fopen("assembler\\program", "r");

    //identificando o tipo de operacao
    fscanf(file,"%s",instruction);
    if(!strcmp(instruction,"add")){
        type = 2;
        fscanf(file,"%s",par1);
        pchr = strchr(par1,',');
        if(pchr!=NULL){
            fscanf(file,"%s",par2);
            args = 2;
            pchr = strchr(par2,',');
            if(pchr!=NULL){
                fscanf(file,"%s",par3);
                args = 3;
            }
        }else{
            args = 1;
        }
    }
    fclose(file);
    //leitura completa

    //inicio de escrita
    file = fopen("simulation\\bin", "w");
    fprintf(file, "%s\n", bin);
    //system("pause");
    return fclose(file);
}
