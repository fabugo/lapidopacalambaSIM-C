.module binary

;Algoritmo de busca binária

.pseg
	lcl	r0, LOWBYTE VET
	lch	r0, HIGHBYTE VET
	loadlit r1,0
	loadlit r2,10
	loadlit r3,5
	loadlit r4, 1				;Ponteiro para o endereço de memória para a saida
	;r5 registrador temporario
	;r6 registrador da posicao corrente

	MAIN:	sub r5,r2,r1
			jf.zero SPLIT		;Se 'end' nao for igual a 'start'
			nop

			load r5,r0			;Neste ponto, o vetor possui tamanho 1
			sub r5,r5,r3
			jt.zero ENDS		;Se 'vetor[start]' for igual ao valor buscado
			nop
			loadlit r6,-1		;Se não for, o elemento não existe no vetor
			j ENDC

	SPLIT:	asr r5,r5			;Divide ('end'-'start') por 2
			add r6,r5,r1 		;Soma com o offset do start
			add r0,r0,r6		;Move o ponteiro do vetor para a possicao corrente
			load r5,r0			;Carrega o valor da posicao atual do vetor
			sub r5,r3,r5
			jt.zero ENDC		;Se o valor corrente é igual ao buscado
			nop
			jt.neg LEFT			;Se o valor corrente for maior que o buscado
			nop
			inca r1,r6			;Posicao corrente descartada
								;O inicio passa a ser a posicao corrente
			j MAIN

	LEFT:	deca r2,r6			;Posicao corrente descartada
								;O fim passa a ser a posicao corrente
			sub r0,r0,r6		;Move o ponteiro do vetor para o inicio dele
			j MAIN

	ENDS:	passa r5,r1
			j END

	ENDC:	passa r5,r6
			j END

	END:	store r4,r5

.dseg
	VET:	.word 1
			.word 2
			.word 3
			.word 4
			.word 5
			.word 6
			.word 7
			.word 8
			.word 9
			.word 10
.end