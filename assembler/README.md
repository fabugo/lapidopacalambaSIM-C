#LAPI DOPACA LAMBA

##Estrutura da Pasta
Nesta pasta estão contidos o montador (assembler.c), arquivos header auxiliares (pasta lib), um arquivo que compila e executa o montador (executar.bat) utilizando como programas de entrada (contidos na pasta input). Além disso, contém uma pasta vazia para saída dos programas (output);

O código fonte do assembler é composto pelo arquivo principal "assembler.c" e alguns arquivos auxiliares, são elas:

* **Reader.h** 		- Utilizado para ler um arquivo de entrada e separá-lo em linhas;

* **Formatter.h** 	- Utilizado para verificar a sintaxe do código fonte, se as instruções e os operandos são validos e se os Labels estão declarados corretamente;

* **Checker.h** 	- Verifica se todos os labels e variáveis utilizadas foram declarados.

Além disso, o assembler também utiliza uma outra biblioteca auxiliar, a string.h, presente na pasta lib na pasta raiz do projeto. Ela contém métodos para manipulação de strings. 


##Testes
Dentro da pasta input há 11 arquivos de testes. São eles:
	* teste1, teste2 e teste3 - testes disponibilizado pelos professores;
	* binary search, bubble sort e fibonacci - testes solicitados pelos professores;
	* op desvio, op const_desvio_reg, op logica_aritmetica, op memoria - Testes extras para testar cada conjunto de instruções separadamante.


##Compilando
Para compilar o projeto use o seguinte comando:

	gcc -o assembler assembler.c ../lib/string.c lib/reader.c lib/formatter.c lib/checker.c

##Executando
Para executar o projeto apenas chame o arquivo resultante da compilação passando como parâmetro o(s) programa(s) de entrada, por exemplo:

	assembler input/teste1.asm input/teste2.asm

A saída do programa será dada na pasta simulador/input, presente na mesma pasta do raiz "lapidopacalamba". Caso o arquivo já exista, ele será sobrescrito.

##Compilar e Executar (Windows)
Caso queria compilar e executar o montador de forma mais rápida, execute o arquvio Executar.bat que contém as instruções que compila o arquivo .c e o executa chamando todos os programas teste da pasta input:

	gcc -o assembler assembler.c ../lib/string.c lib/reader.c lib/formatter.c lib/checker.c
	
	assembler "input/teste1.asm" "input/teste2.asm" "input/teste3.asm" "input/fibonacci.asm" "input/binary search.asm" "input/bubble sort.asm"