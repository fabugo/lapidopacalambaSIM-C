.module binary

;Algoritmo de busca binária

.pseg
	lcl	r0, LOWBYTE VET
	lch	r0, HIGHBYTE VET
	loadlit r1,0
	loadlit r2,10
	loadlit r3,5
	;r4 registrador temporario
	;r5 registrador da posicao corrente
	;r6 registrador para a saida da execucao

	MAIN:	sub r4,r2,r1
			jf.zero SPLIT		;Se 'end' nao for igual a 'start'
			;nop

			load r4,r0			;Neste ponto, o vetor possui tamanho 1
			sub r4,r4,r3
			jt.zero ENDS		;Se 'vetor[start]' for igual ao valor buscado
			;nop
			loadlit r5,-1		;Se não for, o elemento não existe no vetor
			j ENDC

	SPLIT:	asr r4,1			;Divide ('end'-'start') por 2
			add r5,r4,r1 		;Soma com o offset do start
			add r0,r0,r5		;Move o ponteiro do vetor para a possicao corrente
			load r4,r0			;Carrega o valor da posicao atual do vetor
			sub r4,r3,r4
			jt.zero ENDC		;Se o valor corrente é igual ao buscado
			;nop
			jt.neg LEFT			;Se o valor corrente for maior que o buscado
			;nop
			passa r1,r5			;O inicio passa a ser a posicao corrente
			j MAIN

	LEFT:	passa r2,r5			;O fim passa a ser a posicao corrente
			sub r0,r0,r5		;Move o ponteiro do vetor para o inicio dele
			j MAIN

	ENDS:	passa r6,r1
			j END

	ENDC:	passa r6,r5
			j END

	END:	;Como finaliza??

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