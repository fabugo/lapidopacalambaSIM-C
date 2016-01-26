#include "stdio.h"
char sum(char ci,char a,char b,char *co);
char *sum32(char *a,char *b,char *co);
int main(int argc, char const *argv[]) {
    char *a  = "001\0";//declaração dos valores a ser operado
    char *b  = "001\0";
    char *co = "\0";//inicializando variavel
    char *result = sum32(a,b,co);
    printf("Result: %s\nCarry out: %s\n",result,co);//exibe os resultados
    return 0;
}
char *sum32(char *a,char *b,char *cof){
    printf("Operandos:\n        %s\n        %s\n",a,b);//exibe valores a serem operados
    int i = 2;
    char *result = "\0";
    char ci = '0';
    char *co = "\0";
    for(i;i>=0;i--){
        result[i]=sum(ci,a[i],b[i],co);// essa chamada ta travando o codigo
        ci = co;//passa a diante o valor do carry
    }
    cof = co;
    return result;
}
char sum(char ci,char a,char b,char *co){
    printf("Operandos:\n        %s\n        %s\n        %s\n",ci,a,b);
    if(ci == '0'){
        if(a==b){
            co = '0';
            return '0';
        }else{
            if(a=='0'){
                co = '1';
            }else if (a=='1'){
                co = '0';
            }
            return '1';
        }
    }else if(ci == '1'){
        if(a!=b){
            co = '0';
            return '0';
        }else{
            if(a=='0'){
                co = '0';
            }else if (a=='1'){
                co = '1';
            }
            return '1';
        }
    }
}
