#include <stdio.h>
#include <string.h>

#include "../lib/string.h"
#include "lib/reader.h"
#include "lib/formatter.h"
#include "lib/checker.h"

struct INSTRUCTION {
    long long int address;
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

Label *jumpers = NULL, *variables = NULL;
Instruction *psegInstr = NULL, *dsegInstr = NULL;

int main(int argc, char *argv[]) {
    char *outputPath;
    int x;
    for(x = 1; x < argc; x++) {
        outputPath = malloc(50);
        sprintf(outputPath, "../simulator/input/program_%d", x);
        start(argv[x], outputPath);
    }

    printf("\nExecucao finalizada, pressione qualquer tecla para fechar\n");
    getch(); //Pausa o terminal
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
    long long int addressCount = 0;
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
    long long int instructionAddress = 0, memoryAddress = 0;
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
                sprintf(temp, "lcl r0,LOWBYTE %s", param);
                dsegInstr->content = temp;
                instr = dsegInstr;
            } else {
                instr->next = malloc(sizeof(Instruction));
                instr = instr->next;
                instr->address = instructionAddress++;
                temp = malloc(100);
                sprintf(temp, "lcl r0,LOWBYTE %s", param);
                instr->content = temp;
            }

            instr->next = malloc(sizeof(Instruction));
            instr = instr->next;
            instr->address = instructionAddress++;
            temp = malloc(100);
            sprintf(temp, "lch r0,HIGHBYTE %s", param);
            instr->content = temp;

            instr->next = malloc(sizeof(Instruction));
            instr = instr->next;
            instr->address = instructionAddress++;
            temp = malloc(100);
            sprintf(temp, "lcl r1,LOWBYTE %d", memoryAddress);
            instr->content = temp;

            instr->next = malloc(sizeof(Instruction));
            instr = instr->next;
            instr->address = instructionAddress++;
            temp = malloc(100);
            sprintf(temp, "lch r1,HIGHBYTE %d", memoryAddress);
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
        long long int increment = instr->address;

        Label *jumper = jumpers;
        while(jumper != NULL) {
            jumper->address += increment+1;
            jumper = jumper->next;
        }

        while((instr = instr->next) != NULL) {
            instr->address += increment+1;
        }
    } else {
        dsegInstr = psegInstr;
    }
}

void replaceLabelsAndVariables() {
    Instruction *instr;
    Label *jumper = jumpers, *variable = variables;

    printf("[A][INFO] Substituindo labels de desvios\n");
    
    while(jumper != NULL) {
        instr = psegInstr;
        while(instr != NULL) {
            if((startWith(instr->content, "lcl ") || startWith(instr->content, "lch ") || startWith(instr->content, "loadlit ")
                || startWith(instr->content, "j ") || startWith(instr->content, "jt.") || startWith(instr->content, "jf."))
                && contains(instr->content, jumper->name)) {

                char *temp = malloc(11);
                sprintf(temp, "%d", jumper->address);
                instr->content = replaceAll(instr->content, jumper->name, temp);
            }
            instr = instr->next;
        }
        jumper = jumper->next;
    }

    printf("[A][INFO] Substituindo labels de variaveis\n");
    while(variable != NULL) {
        instr = psegInstr;
        while(instr != NULL) {
            if((startWith(instr->content, "lcl ") || startWith(instr->content, "lch ") || startWith(instr->content, "loadlit "))
                && contains(instr->content, variable->name)) {

                char *temp = malloc(10);
                sprintf(temp, "%d", variable->address);
                instr->content = replaceAll(instr->content, variable->name, temp);
            }
            instr = instr->next;
        }
        variable = variable->next;
    }
}

char *getParam(char *instr, int param) {
    int first = indexOf(instr, ','), last = lastIndexOf(instr, ','), space = indexOf(instr, ' ');
    char *temp;
    if(param == 1) { //Entre o espaço e a primeira virgula
        temp = substring(instr, space+1, first-1);
    } else if(param == 2) { //Entre a primeira e a ultima virgula
        temp = substring(instr, first+1, last-1);
    } else if(param == 3) { //Após a ultima virgula
        temp = strOffset(instr, last+1);
    } else { //Após o espaço
        temp = strOffset(instr, space+1);
    }

    if(startWith(temp, "LOWBYTE ")) {
        temp = strOffset(temp, indexOf(temp, ' ') + 1);
        char *bin = decimalToBinary(temp, 32);
        return strOffset(bin, 16);
    } else if(startWith(temp, "HIGHBYTE ")) {
        temp = strOffset(temp, indexOf(temp, ' ') + 1);
        char *bin = decimalToBinary(temp, 32);
        return substring(bin, 0, 15);
    } else if(startWith(temp, "r")) {
        removeAll(temp, 0, strlen(temp), 'r');
        return decimalToBinary(temp, 4);
    } else {
        return decimalToBinary(temp, 16);
    }
}

char *getInstrBits(char *instr) {
    char *temp = malloc(33);

    //Instruções Lógicas e Aritméticas
    if(startWith(instr, "add ")) {
        //001 00000 ssss ssss ssss 000000000000
        sprintf(temp, "00100000%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "addinc ")) {
        //001 00001 ssss ssss ssss 000000000000
        sprintf(temp, "00100001%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "inca ")) {
        //001 00011 ssss ssss 0000 000000000000
        sprintf(temp, "00100011%s%s0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "subdec ")) {
        //001 00100 ssss ssss ssss 000000000000
        sprintf(temp, "00100100%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "sub ")) {
        //001 00101 ssss ssss ssss 000000000000
        sprintf(temp, "00100101%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "deca ")) {
        //001 00110 ssss ssss 0000 000000000000
        sprintf(temp, "00100110%s%s0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "lsl ")) {
        //001 01000 ssss ssss 0000 000000000000
        sprintf(temp, "00101000%s%s0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "asr ")) {
        //001 01001 ssss ssss 0000 000000000000
        sprintf(temp, "00101001%s%s0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "zeros ")) {
        //001 10000 ssss 0000 0000 000000000000
        sprintf(temp, "00110000%s00000000000000000000", getParam(instr, 0));
    } else if(startWith(instr, "and ")) {
        //001 10001 ssss ssss ssss 000000000000
        sprintf(temp, "00110001%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "andnota ")) {
        //001 10010 ssss ssss ssss 000000000000
        sprintf(temp, "00110010%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "passb ")) {
        //001 10011 ssss 0000 ssss 000000000000
        sprintf(temp, "00110011%s0000%s000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "andnotb ")) {
        //001 10100 ssss ssss ssss 000000000000
        sprintf(temp, "00110100%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "passa ")) {
        //001 10101 ssss ssss 0000 000000000000
        sprintf(temp, "00110101%s%s0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "xor ")) {
        //001 10110 ssss ssss ssss 000000000000
        sprintf(temp, "00110110%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "or ")) {
        //001 10111 ssss ssss ssss 000000000000
        sprintf(temp, "00110111%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "nand ")) {
        //001 11000 ssss ssss ssss 000000000000
        sprintf(temp, "00111000%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "xnor ")) {
        //001 11001 ssss ssss ssss 000000000000
        sprintf(temp, "00111001%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "passnota ")) {
        //001 11010 ssss ssss 0000 000000000000
        sprintf(temp, "00111010%s%s0000000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "ornota ")) {
        //001 11011 ssss ssss ssss 000000000000
        sprintf(temp, "00111011%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "passnotb ")) {
        //001 11100 ssss 0000 ssss 000000000000
        sprintf(temp, "00111100%s0000%s000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "ornotb ")) {
        //001 11101 ssss ssss ssss 000000000000
        sprintf(temp, "00111101%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "nor ")) {
        //001 11110 ssss ssss ssss 000000000000
        sprintf(temp, "00111110%s%s%s000000000000", getParam(instr, 1), getParam(instr, 2), getParam(instr, 3));
    } else if(startWith(instr, "ones ")) {
        //001 11111 ssss 0000 0000 000000000000
        sprintf(temp, "00111111%s00000000000000000000", getParam(instr, 0));
    
    //Instruções com Constante
    } else if(startWith(instr, "loadlit ")) {
        //010 01100 ssss 0000 ssssssssssssssss
        sprintf(temp, "01001100%s0000%s", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "lcl ")) {
        //010 01101 ssss ssss ssssssssssssssss
        sprintf(temp, "01001101%s%s%s", getParam(instr, 1), getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "lch ")) {
        //010 01110 ssss ssss ssssssssssssssss
        sprintf(temp, "01001110%s%s%s", getParam(instr, 1), getParam(instr, 1), getParam(instr, 3));

    //Instruções de Memória
    } else if(startWith(instr, "load ")) {
        //100 0000 0 ssss 0000 ssss 000000000000
        sprintf(temp, "10000000%s0000%s000000000000", getParam(instr, 1), getParam(instr, 3));
    } else if(startWith(instr, "store ")) {
        //100 0000 1  0000 ssss ssss 000000000000
        sprintf(temp, "100000010000%s%s000000000000", getParam(instr, 3), getParam(instr, 1));

    //Instruções de Desvio
    } else if(startWith(instr, "j ")) {
        //000 00 010 000000000 000 ssssssssssss
        sprintf(temp, "00000010000000000000%s", strOffset(getParam(instr, 0), 4));
    } else if(startWith(instr, "jf.")) {
        //000 00 000 000000000 sss ssssssssssss
        char *cond = substring(instr, 3, indexOf(instr, ' ') - 1);
        char c[4];
        if(strEquals(cond, "true")) {
            strcpy(c, "000");
        } else if(strEquals(cond, "neg")) {
            strcpy(c, "001");
        } else if(strEquals(cond, "zero")) {
            strcpy(c, "010");
        } else if(strEquals(cond, "carry")) {
            strcpy(c, "100");
        } else if(strEquals(cond, "negzero")) {
            strcpy(c, "101");
        } else if(strEquals(cond, "overflow")) {
            strcpy(c, "111");
        }
        sprintf(temp, "00000000000000000%s%s", c, strOffset(getParam(instr, 0), 4));
    } else if(startWith(instr, "jt.")) {
        //000 00 001 000000000 sss ssssssssssss
        char *cond = substring(instr, 3, indexOf(instr, ' ') - 1);
        char c[4];
        if(strEquals(cond, "true")) {
            strcpy(c, "000");
        } else if(strEquals(cond, "neg")) {
            strcpy(c, "001");
        } else if(strEquals(cond, "zero")) {
            strcpy(c, "010");
        } else if(strEquals(cond, "carry")) {
            strcpy(c, "100");
        } else if(strEquals(cond, "negzero")) {
            strcpy(c, "101");
        } else if(strEquals(cond, "overflow")) {
            strcpy(c, "111");
        }
        sprintf(temp, "00000001000000000%s%s", c, strOffset(getParam(instr, 0), 4));
    
    //Instruções de Desvio por Registrador
    } else if(startWith(instr, "jal ")) {
        //           r15  
        //111 00 011 1111 0000 ssss 000000000000
        sprintf(temp, "1100001111110000%s000000000000", getParam(instr, 0));
    } else if(startWith(instr, "jr ")) {
        //111 00 100 0000 0000 ssss 000000000000
        sprintf(temp, "1100010000000000%s000000000000", getParam(instr, 0));

    //Instrução nop
    } else if(strEquals(instr, "nop")) {
        //jf.TRUE 0
        //000 00 000 000000000 000 000000000000
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
                //printf("%s   -    %s\n", temp, instr->content);//DEBUG
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