#include <stdio.h>
#include <string.h>

#include "reader.h"

int main(int argc, char *argv[]) {
    Instr *MI = read("input");
    Instr *pc = MI;
    
    while(pc != NULL) {
    	int type, OP;
    	char *tempBin = substring(pc-content,0,2);
    	itoa(type,tempBin,2);
    	tempBin = substring(pc-content,3,8);
		itoa(OP,tempBin,2);

		if(type == 1){
			printf("LOGICA ARITIMETICA\n");
			switch (OP){
				case 0: break
				case 1: break
				case 3: break
				case 4: break
				case 5: break
				case 6: break
				case 8: break
				case 9: break
				case 16: break
				case 17: break
				case 18: break
				case 19: break
				case 20: break
				case 21: break
				case 22: break
				case 23: break
				case 24: break
				case 25: break
				case 26: break
				case 27: break
				case 28: break
				case 29: break
				case 30: break
				case 31: break
			}
		}else if(type == 2){
			printf("CONSTANTE\n");
			switch (OP){
				case 2: break
				case 1: break
				case 3: break
			}
		}else if(type == 4){
			printf("MEMORIA\n");
			switch (OP){
				case 0: break
				case 1: break
			}
		}else if(type == 5){
			printf("DESVIO\n");
			switch (OP){
				case 0: break
				case 1: break
				case 2: break
			}
		}else if(type == 6){
			printf("DESVIO POR REGISTRADOR\n");
			switch (OP){
				case 0: break
				case 1: break
			}
		}else if(type == 0){
			printf("NOP\n");
		}else {
			printf("a casa caiu que esse 'itoa()' nao ta funcionando\n");
		}


        pc = pc->next;
    }
}
