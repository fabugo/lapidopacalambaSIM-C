.module binary

;Algoritmo de busca binária

.pseg
	lcl	vetor, LOWBYTE VET
	lch	vetor, HIGHBYTE VET
	loadlit start,0
	loadlit end,10
	loadlit value,5
	;temp
	;current
	;output

	MAIN:	sub temp,end,start
			jf.zero SPLIT				;Se 'end' nao for igual a 'start'
			;nop

			load temp,vetor				;Neste ponto, o vetor possui tamanho 1
			sub temp,temp,value
			jt.zero ENDS				;Se 'vetor[start]' for igual ao valor buscado
			;nop
			loadlit current,-1			;Se não for, o elemento não existe no vetor
			j ENDC

	SPLIT:	asr temp,1					;Divide ('end'-'start') por 2
			add current,temp,start 		;Soma com o offset do start
			add vetor,vetor,current		;Move o ponteiro do vetor para a possicao corrente
			load temp,vetor				;Carrega o valor da posicao atual do vetor
			sub temp,value,temp
			jt.zero ENDC				;Se o valor corrente é igual ao buscado
			;nop
			jt.neg LEFT					;Se o valor corrente for maior que o buscado
			;nop
			passa start,current			;O inicio passa a ser a posicao corrente
			j MAIN

	LEFT:	passa end,current			;O fim passa a ser a posicao corrente
			sub vetor,vetor,current		;Move o ponteiro do vetor para o inicio dele
			j MAIN

	ENDS:	passa output,start
			j END

	ENDC:	passa output,current
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