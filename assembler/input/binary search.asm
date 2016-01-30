.module binary

;Algoritmo de busca binária

.pseg
	loadlit r10, 15					;Ponteiro para o endereço de memória para a saida

	lcl	r0, LOWBYTE VET 			;Carrega os bites menos significativos do endereço do
									;vetor nos bits menos significativos de r0
	lch	r0, HIGHBYTE VET 			;Carrega os bites mais significativos do endereço do
									;vetor nos bits mais significativos de r0	
	load r1, r0						;Carrega o elemento buscado
	
	inca r0, r0 					;Incrementa o vetor
	load r3, r0						;Carrega a quantidade de elementos do vetor
	deca r3, r3
	zeros r2
	inca r0, r0 					;Incrementa o vetor para o primeiro elemento a ser ordenado
	
	MAIN:	sub r5, r2, r3 		;while (r2 <= r3)
			jf.negzero NFOUND		;Se 'r3' não for maior ou igual a 'r2'
			nop

			add r4, r2, r3 			;'r4' = 'r2' + 'r3'
			asr r4, r4				;'r4' - 'r4' / 2

			add r0, r0, r4
			load r5, r0			;'r5' = r0['r4']
			sub r5, r5, r1 		;Se 'r5' = 'r1', return 'r4'
			jt.zero END
			nop

			jt.neg RIGHT			;Se 'r1' > r5
			nop
			deca r3, r4				;'r3' = 'r4' - 1
			j MAIN

	RIGHT:	inca r2, r4				;'r2' = 'r4' + 1
			sub r0, r0, r4
			j MAIN
	
	NFOUND: loadlit r4, -1
			j END

	END:	store r10,r4			;Armazena na memória o valor da posicao do elemento

	HALT: j HALT

.dseg
	VET:	
			.word 4
			.word 10
				.word 1
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