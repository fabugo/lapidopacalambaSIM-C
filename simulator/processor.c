/*
	Arquivo que inicializa o simulador, carrega as instruções e inicia a execução do programa
*/

#include <stdio.h>
#include <string.h>

#include "defs.h"
#include "reader.h"
#include "../lib/string.h"

#include "modules/memory_instruction.h"
#include "modules/unit_control.h"
#include "modules/signal_extender.h"
#include "modules/register_bank.h"
#include "modules/mx_se.h"
#include "modules/alu.h"
#include "modules/data_memory.h"
#include "modules/register_flags.h"
#include "modules/tester_flags.h"
#include "modules/mx_pc.h"
#include "modules/mx_rb.h"
#include "modules/program_counter.h"
#include "modules/add.h"

int main(int argc, char *argv[]) {
	/***********Zera todas os dados dos componentes***********/
	RST_MI('1');				//MEMORY INSTRUCTION
	strcpy(uc.OP_ALU, "00000"); //UNIT CONTROL
    strcpy(uc.OP_TF, "111");
    uc.W_RB = '0';
    uc.W_DM = '0';
    strcpy(uc.W_RF, "000");
    RST_RB('1');				//REGISTER BANK
	RST_SE('1');				//SIGNAL EXTENDER
	strcpy(mx_se.output, ZERO);	//MX_SE
    RST_ALU('1');				//ALU
	RST_DM('1');				//DATA MEMORY
	RST_RF('1');				//REGISTER FLAGS
	RST_TF('1');				//TESTER FLAGS
	strcpy(mx_pc.output, ZERO);	//MX_PC
	strcpy(mx_rb.output, ZERO);	//MX_RB
	RST_PC('1');				//PROGRAM COUNTER
	strcpy(add.output, ZERO);	//MX_RB
	/*********************************************************/

	/***Liga as saídas dos componentes à entradas de outros*****/
	mi.input = (char*) &pc.output;				//MEMORY INSTRUCTION
	uc.TYPE_OP = (char*) &mi.output;			//UNIT CONTROL
    rbank.input_RA = (char*) &mi.output;		//REGISTER BANK
    rbank.input_RB = (char*) &mi.output;
    rbank.input_WC = (char*) &mi.output;
    rbank.input_WPC = (char*) &mx_rb.output;
    se.input = (char*) &mi.output;				//SIGNAL EXTENDER
	mx_se.input_RB = (char*) &rbank.output_PRB;	//MX_SE
	mx_se.input_SE = (char*) &se.output;
	alu.input_A = (char*) &rbank.output_PRA;	//ALU
    alu.input_B = (char*) &mx_se.output;
    dm.input = (char*) &rbank.output_PRA;		//DATA MEMORY
	dm.address = (char*) &rbank.output_PRB;
	rf.input_OSCZ = (char*) &alu.OSCZ;		//REGISTER FLAGS
	tf.input_OSCZ = (char*) &rf.output_OSCZ;
	tf.cond = (char*) &mi.output;				//TESTER FLAGS
	mx_pc.input_ALU = (char*) &alu.output;		//MX_PC
	mx_pc.input_ADD = (char*) &add.output;
	mx_rb.input_PC = (char*) &mx_pc.output;		//MX_RB
	mx_rb.input_DM = (char*) &dm.output;
	mx_rb.input_ALU = (char*) &alu.output;
	pc.input = (char*) &mx_pc.output;			//PROGRAM COUNTER
	add.input = (char*) &pc.output;				//ADD
	/*********************************************************/

	if(argc > 1) {
        /******Carrega as instruções na memória de instrução******/
		Instr *instr = read(argv[1]); //Lê o arquivo de entrada
		if(instr != NULL) {
			int x;
			for(x = 0; x < MI_SIZE && instr != NULL; x++) {
			//Percorre instrução a instrução copiando-as para a memória de instruções
				strcpy(mi.instruction[x], instr->content);
				instr = instr->next;
			}
			/*********************************************************/

			UC_run();
		}
    }
}