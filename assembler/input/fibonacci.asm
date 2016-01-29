.module Fibonacci
.pseg
	lcl	r0, LOWBYTE POS 		
	lch	r0, HIGHBYTE POS
	load r0,r0			;Carrega o valor da posição do elemento desejado

	loadlit r1, 0 		;Primeiro valor da sequencia
	loadlit r2, 1		;Segundo valor da sequencia
	loadlit r5, 10		;Ponteiro da memoria onde sera armazenado o resultado
LOOP: add r4,r2,r1		;Armazena em r4 a soma dos dois ultimos elementos
	passa r1,r2			;Copia valor
	passa r2,r4
	deca r0,r0			;Decrementa r0 até que chegue a 0, finalizando o algoritmo
	jt.zero FIM			;Verificacao do valor em r0
	nop
	j LOOP				;Se r0 não for 0, ele pula para o inicio do loop
FIM: store r5,r4		;Armazena no endereço presente em 'r5' o valor presente em 'r4'

HALT: j HALT

.dseg
POS:	.word 10
.end