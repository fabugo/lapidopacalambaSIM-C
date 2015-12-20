#include <stdio.h>
#include <string.h>

#include "string.h"
#include "reader.h"
#include "formatter.h"
#include "checker.h"

struct INSTRUCTION {
    int address;
    char *content;
    struct INSTRUCTION *next;
};
typedef struct INSTRUCTION Instruction;

void start(char *input, char *outputPath);

int mount(Line *line, char *outputPath);

void createPseg(Line *line);

void createDseg(Line *line);

void joinSegs();

void replaceLabelsAndVariables();

int writeBits(char *outputPath);

int decimalToBinary(char *value);

Label *jumpers = NULL, *variables = NULL;
Instruction *psegInstr = NULL, *dsegInstr = NULL;

int main(int argc, char *argv[]) {
    char *outputPath;
    int x;
    for(x = 1; x < argc; x++) {
        outputPath = malloc(50);
        sprintf(outputPath, "output/program_%d", x);
        start(argv[x], outputPath);
    }
}

void start(char *input, char *outputPath) {
    jumpers = NULL;
    variables = NULL;
    psegInstr = NULL;
    dsegInstr = NULL;

    printf("\n[A][INFO] Lendo o arquivo \"%s\"\n", input);
    Line *line = read(input);
    if(line != NULL) {
        printf("[A][INFO] Analisando o conteudo lido\n");
        if(formatInstructions(line) == 1) {
            printf("[A][INFO] Verificando Labels\n");
            if(check(line) == 1)
                if(mount(line, outputPath) == 1)
                    printf("\n[A][INFO] Montagem concluida com sucesso\n");
        }
    }
    printf("-----------------------------------------------------------\n\n");
}

int mount(Line *line, char *outputPath) {
    Line *aux = line;
    while((aux = aux->next) != NULL && (psegInstr == NULL || dsegInstr == NULL)) {
        if(strEquals(aux->text, ".pseg"))
            createPseg(aux);
        if(strEquals(aux->text, ".dseg"))
            createDseg(aux);
    }

    joinSegs();
    
    replaceLabelsAndVariables();

    return writeBits(outputPath);
}

void createPseg(Line *line) {
    int addressCount = 0;
    Instruction *instr = NULL;
    Label *jumper = NULL;

    printf("[A][INFO] Listando labels e instrucoes do programa\n");
    while((line = line->next) != NULL && line->text[0] != '.') {
        char *content;
        int index = indexOf(line->text, ':');
        if(index > -1) {
            if(jumper == NULL) {
                jumpers = malloc(sizeof(Label));
                jumpers->address = addressCount;
                jumpers->name = substring(line->text, 0, index-1);
                jumpers->next = NULL;
                jumper = jumpers;
            } else {
                jumper->next = malloc(sizeof(Label));
                jumper = jumper->next;
                jumper->address = addressCount;
                jumper->name = substring(line->text, 0, index-1);
                jumper->next = NULL;
            }
            content = strOffset(line->text, index+2);
        } else {
            content = line->text;
        }

        if(instr == NULL) {
            psegInstr = malloc(sizeof(Instruction));
            psegInstr->address = addressCount++;
            psegInstr->content = content;
            psegInstr->next = NULL;
            instr = psegInstr;
        } else {
            instr->next = malloc(sizeof(Instruction));
            instr = instr->next;
            instr->address = addressCount++;
            instr->content = content;
            instr->next = NULL;
        }
    }
}

void createDseg(Line *line) {
    int instructionAddress = 0, memoryAddress = 0;
    Instruction *instr = NULL;
    Label *variable = NULL;

    line = line->next;
    if(line != NULL) {
        printf("[A][INFO] Listando variaveis e criando instrucoes de carregamento das mesmas\n");
    }
    while(line != NULL && line->text[0] != '.') {
        if(variable == NULL) {
            variables = malloc(sizeof(Label));
            variables->address = memoryAddress;
            variables->name = substring(line->text, 0, strlen(line->text)-2);
            variables->next = NULL;
            variable = variables;
        } else {
            variable->next = malloc(sizeof(Label));
            variable = variable->next;
            variable->address = memoryAddress;
            variable->name = substring(line->text, 0, strlen(line->text)-2);
            variable->next = NULL;
        }

        char *param;
        char *temp;
        while(startWith((line = line->next)->text, ".word ")) {
            param = strOffset(line->text, 6);
            if(instr == NULL) {
                dsegInstr = malloc(sizeof(Instruction));
                dsegInstr->address = instructionAddress++;
                temp = malloc(100);
                sprintf(temp, "loadlit r0,LOWBYTE %s", param);
                dsegInstr->content = temp;
                instr = dsegInstr;
            } else {
                instr->next = malloc(sizeof(Instruction));
                instr = instr->next;
                instr->address = instructionAddress++;
                temp = malloc(100);
                sprintf(temp, "loadlit r0,LOWBYTE %s", param);
                instr->content = temp;
            }

            instr->next = malloc(sizeof(Instruction));
            instr = instr->next;
            instr->address = instructionAddress++;
            temp = malloc(100);
            sprintf(temp, "loadlit r0,HIGHBYTE %s", param);
            instr->content = temp;

            instr->next = malloc(sizeof(Instruction));
            instr = instr->next;
            instr->address = instructionAddress++;
            temp = malloc(100);
            sprintf(temp, "loadlit r1,LOWBYTE %d", memoryAddress);
            instr->content = temp;

            instr->next = malloc(sizeof(Instruction));
            instr = instr->next;
            instr->address = instructionAddress++;
            temp = malloc(100);
            sprintf(temp, "loadlit r1,HIGHBYTE %d", memoryAddress);
            instr->content = temp;

            instr->next = malloc(sizeof(Instruction));
            instr = instr->next;
            instr->address = instructionAddress++;
            temp = "store r1,r0";
            instr->content = temp;
            instr->next = NULL;

            memoryAddress++;
        }

        if(variable->address == memoryAddress) {
            memoryAddress++;
        }
    }
}

void joinSegs() {
    Instruction *instr = dsegInstr;

    if(instr != NULL) {
        printf("[A][INFO] Mesclando segmentos de dados e programas\n");
        while(instr->next != NULL) {
            instr = instr->next;
        }
        instr->next = psegInstr;
        int increment = instr->address;

        Label *jumper = jumpers;
        while(jumper != NULL) {
            jumper->address += increment;
            jumper = jumper->next;
        }

        while((instr = instr->next) != NULL) {
            instr->address += increment;
        }
    }
}

void replaceLabelsAndVariables() {
    Instruction *instr;
    Label *jumper = jumpers, *variable = variables;

    printf("[A][INFO] Substituindo labels de desvios\n");
    instr = psegInstr;
    while(jumper != NULL) {
        while(instr != NULL) {
            if((startWith(instr->content, "lcl ") || startWith(instr->content, "lch ") || startWith(instr->content, "loadlit ")
                || startWith(instr->content, "j ") || startWith(instr->content, "jt.") || startWith(instr->content, "jf."))
                /*&& contains(instr->content, jumper->name)*/) {

                char *temp = malloc(11);
                sprintf(temp, "%d", jumper->address);
                //replaceAll(instr->content, jumper->name, temp);
            }
            instr = instr->next;
        }
        jumper = jumper->next;
    }

    printf("[A][INFO] Substituindo labels de variaveis\n");
    instr = psegInstr;
    while(variable != NULL) {
        while(instr != NULL) {
            if((startWith(instr->content, "lcl ") || startWith(instr->content, "lch ") || startWith(instr->content, "loadlit "))
                /*&& contains(instr->content, variable->name)*/) {

                char *temp = malloc(10);
                sprintf(temp, "%d", variable->address);
                //replaceAll(instr->content, variable->name, temp);
            }
            instr = instr->next;
        }
        variable = variable->next;
    }
}

int decimalToBinary(char *value) {
    int v = atoi(value);
    char *temp = malloc(33);
    int x;

    for(x=0; x<8; x++) {
        if((v & 0x80) !=0) {
            temp[x] = '1';
        } else {
            temp[x] = '0';
        }
        v = v<<1;
    }
    temp[x] = '\0';

    return atoi(temp);
}

int getParam(char *instr, int param) {
    int first = indexOf(instr, ','), last = lastIndexOf(instr, ','), space = indexOf(instr, ' ');
    char *temp;
    if(param == 1) {
        temp = substring(instr, space+1, first-1);
    } else if(param == 2) {
        temp = substring(instr, first+1, last-1);
    } else if(param == 3) {
        temp = strOffset(instr, last+1);
    } else {
        temp = strOffset(instr, space+1);
    }

    removeAll(temp, 0, strlen(temp), 'r');
    return decimalToBinary(temp);
}

char *getInstrBits(char *instr) {
    char *temp = malloc(33);

    //Instruções Lógicas e Aritméticas
    if(startWith(instr, "add ")) {
        sprintf(temp, "00100000%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "addinc ")) {
        sprintf(temp, "00100001%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "inca ")) {
        sprintf(temp, "00100011%04d%04d0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "subdec ")) {
        sprintf(temp, "00100100%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "sub ")) {
        sprintf(temp, "00100101%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "deca ")) {
        sprintf(temp, "00100110%04d%04d0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "lsl ")) {
        sprintf(temp, "00101000%04d%04d0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "asr ")) {
        sprintf(temp, "00101001%04d%04d0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "zeros ")) {
        sprintf(temp, "00110000%04d00000000000000000000", getParam(instr, 0));
    } else if(startWith(instr, "and ")) {
        sprintf(temp, "00110001%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "andnota ")) {
        sprintf(temp, "00110010%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "passb ")) {
        sprintf(temp, "00110011%04d0000%04d000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "andnotb ")) {
        sprintf(temp, "00110100%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "passa ")) {
        sprintf(temp, "00110101%04d%04d0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "xor ")) {
        sprintf(temp, "00110110%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "or ")) {
        sprintf(temp, "00110111%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "nand ")) {
        sprintf(temp, "00111000%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "xnor ")) {
        sprintf(temp, "00111001%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "passnota ")) {
        sprintf(temp, "00111010%04d%04d0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "ornota ")) {
        sprintf(temp, "00111011%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "passnotb ")) {
        sprintf(temp, "00111100%04d0000%04d000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "ornotb ")) {
        sprintf(temp, "00111101%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "nor ")) {
        sprintf(temp, "00111110%04d%04d%04d000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "ones ")) {
        sprintf(temp, "00111111%04d00000000000000000000", getParam(instr, 0));
    
    //Instruções com Constante
    } else if(startWith(instr, "loadlit ")) {
        sprintf(temp, "01000010%04d0000%016d", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "lcl ")) {
        sprintf(temp, "01000001%04d0000%016d", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "lch ")) {
        sprintf(temp, "01000011%04d0000%016d", getParam(instr, 1), getParam(instr, 3));

    //Instruções de Memória
    } else if(startWith(instr, "load ")) {
        sprintf(temp, "10000000%04d%04d0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "store ")) {
        sprintf(temp, "100000010000%04d%04d000000000000", getParam(instr, 1), getParam(instr, 3));

    //Instruções de Desvio
    } else if(startWith(instr, "j ")) {
        sprintf(temp, "10100000000000000000%012d", getParam(instr, 0));
    } else if(startWith(instr, "jt.")) {
        char *cond = substring(instr, 3, indexOf(instr, ' ') - 1);
        int c;
        if(strEquals(cond, "neg")) {
            c = 1;
        } else if(strEquals(cond, "zero")) {
            c = 10;
        } else if(strEquals(cond, "carry")) {
            c = 100;
        } else if(strEquals(cond, "negzero")) {
            c = 101;
        } else if(strEquals(cond, "true")) {
            c = 110;
        } else if(strEquals(cond, "overflow")) {
            c = 111;
        }
        sprintf(temp, "1010001000000000%04d%012d", c, getParam(instr, 0));
    } else if(startWith(instr, "jf.")) {
        char *cond = substring(instr, 3, indexOf(instr, ' ') - 1);
        int c;
        if(strEquals(cond, "neg")) {
            c = 1;
        } else if(strEquals(cond, "zero")) {
            c = 10;
        } else if(strEquals(cond, "carru")) {
            c = 100;
        } else if(strEquals(cond, "negzero")) {
            c = 101;
        } else if(strEquals(cond, "true")) {
            c = 110;
        } else if(strEquals(cond, "overflow")) {
            c = 111;
        }
        sprintf(temp, "1010010000000000%04d%012d", c, getParam(instr, 0));
    
    //Instruções de Desvio por Registrador
    } else if(startWith(instr, "jal ")) {
        sprintf(temp, "1100000000000000%04d000000000000", getParam(instr, 0));
    } else if(startWith(instr, "jr ")) {
        sprintf(temp, "1100000100000000%04d000000000000", getParam(instr, 0));

    //Instrução nop
    } else if(strEquals(instr, "nop")) {
        sprintf(temp, "%032d", 0);

    } else {
        temp = NULL;
    }

    return temp;
}

int writeBits(char *outputPath) {
    printf("[A][INFO] Codificando instrucoes\n");
    Instruction *instr = dsegInstr;
    char *temp;
    FILE *outputFile = fopen(outputPath, "w");

    if(outputFile != NULL) {
        while(instr != NULL) {
            temp = getInstrBits(instr->content);

            if(temp != NULL) {
                fprintf(outputFile, "%s\n", temp);
                instr = instr->next;
            } else {
                printf("[A][ERRO] Erro ao codificar instrucao: %s\n", instr->content);
                return 0;
            }
        }
        return 1;
        fclose(outputFile);
    }

    printf("[A][ERRO] Erro ao abrir arquivo de saida\n");
    return 0;
}

//SUBSTITUICAO DOS LABELS DE DESVIO E VARIAVEIS
//LOWBYTE e HIGHBYTE NA CODIFICACAO
//FORMATO DO JUMPER - TAMANHO MALUCO
//TAMANHO DO ENDEREÇO DA MEMÓRIA DE INSTRUÇÕES 32 - JA QUE USA LOW E HIGH P CARREGA-LOS
//TAMANHO DO ENDEREÇO DA MEMÓRIA DE DADOS 32 - JA QUE USA LOW E HIGH P CARREGA-LOS
//NUMEROS NEGATIVOS - O QUE FAZER?