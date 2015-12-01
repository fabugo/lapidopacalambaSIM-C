#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[]) {
    FILE *file;
    file = fopen("program", "r");
    char instruction[6],
                par1[4],
                par2[4],
                par3[4];

    fscanf(file,"%s",instruction);
    if(!strcmp(instruction,"add")){
        fscanf(file,"%s",par1);
        fscanf(file,"%s",par2);
        fscanf(file,"%s",par3);
    }
    fclose(file);

    file = fopen("bin", "w");
    fprintf(file, "%s %s %s %s","0000 0000 0000 0000 0001 0000 0010 0011",par1,par2,par3);



    system("pause");
    return fclose(file);
}
