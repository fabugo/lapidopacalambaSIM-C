.module Fibonacci 
.pseg 
	loadlit r0, 10 		;Armazena no r0 a posição desejada
	loadlit r1, 0 		;Primeiro valor da sequencia
	loadlit r2, 1		;Segundo valor da sequencia
	loadlit r5, 1023	;Registrador de saída
	nop
LOOP: add r4,r2,r1		;Armazena em r4 a soma dos dois ultimos elementos
	passa r1,r2
	passa r2,r4
	deca r0,r0			;Decrementa r0 até que chegue a 0, finalizando o algoritmo
	jt.zero FIM 
	nop
	j LOOP				;Se r0 não for 0, ele pula para o inicio do loop
	nop
FIM: store r5,r4
.dseg
.end
