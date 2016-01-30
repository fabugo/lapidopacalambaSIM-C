.module Fibonacci 		;0 1 1 2 3 5 8 13 21 34...
.pseg
	lcl	r0, LOWBYTE POS 		
	lch	r0, HIGHBYTE POS
	load r0,r0			;Carrega o valor da posição do elemento desejado
	loadlit r3, 15		;Ponteiro da memoria onde sera armazenado o resultado

	loadlit r1, 0		;Se POS <= 0, encerra
	add r0, r0, r1
	jt.negzero HALT
	nop

	deca r4, r0			;Se POS = 1, o resultado é 0, r4 = 1 - 1 = 0
	jt.zero FIM
	nop

	deca r1, r4			;Se r1 = 0, r4 = 1. Logo, se deseja o 2º elemento = 1
	jt.zero FIM	
	nop

	deca r0, r0			;;Se for a partir do terceiro, decrementa 2
	deca r0, r0

	loadlit r1, 0 		;Primeiro valor da sequencia
	loadlit r2, 1		;Segundo valor da sequencia
						;Somando r1 e r2, se tem o terceiro elemento			

LOOP: add r4,r2,r1		;Armazena em r4 a soma dos dois ultimos elementos
	passa r1,r2			;Copia valor
	passa r2,r4
	deca r0,r0			;Decrementa r0 até que chegue a 0, finalizando o algoritmo
	jt.zero FIM			;Verificacao do valor em r0
	nop
	j LOOP				;Se r0 não for 0, ele pula para o inicio do loop
FIM: store r3,r4		;Armazena no endereço presente em 'r3' o valor presente em 'r4'

HALT: j HALT

.dseg
POS:	.word 10
.end