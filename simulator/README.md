##Compilando
Para compilar o simulador use o seguinte comando:

	gcc -o processor processor.c ../lib/string.c modules/program_counter.c modules/memory_instruction.c modules/signal_extender.c modules/register_bank.c modules/data_memory.c modules/alu.c modules/register_flags.c modules/tester_flags.c modules/unit_control.c modules/mx_pc.c modules/mx_rb.c modules/mx_se.c modules/add.c

##Executando
Para executar o projeto apenas chame o arquivo resultante da compilação passando como parâmetro o(s) programa(s) de entrada, por exemplo:

	processor "<NOME_DO_ARQUIVO_DE_ENTRADA>"

##Compilar e Executar (Windows)
Caso queria compilar e executar o simulador de forma mais rápida, execute o arquvio executar.bat que contém as instruções que compila o arquivo .c e o executa chamando o arquivo input/program_1:

	cls
	
	gcc -o processor processor.c ../lib/string.c modules/program_counter.c modules/memory_instruction.c modules/signal_extender.c modules/register_bank.c modules/data_memory.c modules/alu.c modules/register_flags.c modules/tester_flags.c modules/unit_control.c modules/mx_pc.c modules/mx_rb.c modules/mx_se.c modules/add.c
	
	processor "input/program_1"