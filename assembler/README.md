#LAPI DOPACA LAMBA

##Estrutura da Pasta
Nesta pasta contém o código fonte do montador e uma subpasta (input) contendo alguns programas teste.

O código fonte do assembler é composto pelo arquivo principal "assembler.c" e algumas bibliotecas auxiliares, são elas:

* **String.h** 		- Contém métodos para manipulação de strings. 
* **Reader.h** 		- Utilizado para ler um arquivo de entrada e separá-lo em linhas.
* **Formatter.h** 	- Utilizado para verificar a sintaxe do código fonte, se as instruções e os operandos são validos e se os Label estão declarados corretamente.
* **Checker.h** 	- Verifica se todos os labels e variáveis utilizadas foram declarados.

##Compilando
Para compilar o projeto use o seguinte comando:

	gcc -o assembler assembler.c string.c reader.c formatter.c checker.c

##Executando
Para executar o projeto apenas chame o arquivo resultante da compilação passando como parâmetro o(s) programa(s) de entrada, por exemplo:

	assembler input/teste1.asm input/teste2.asm...

A saída do programa será dada na pasta output, presente na mesma pasta do assembler (se ela não existir, deve ser criada manualmente) numerando os programas de acordo com a entrada (teste1.asm = program_1; teste2.asm = program_2...)