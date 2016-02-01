.module binary

.pseg
	loadlit r10, 15					;Ponteiro para o endereço de memória para a saida
	
	lcl	r0, LOWBYTE VET
	lch	r0, HIGHBYTE VET 			;r0 = &Vetor
	lcl	r1, LOWBYTE ELEM
	lch	r1, HIGHBYTE ELEM
	load r1, r1						;r1 = Elemento buscado

	zeros r2						;r2 = Primeira posição do vetor
	lcl	r3, LOWBYTE SIZE
	lch	r3, HIGHBYTE SIZE
	load r3, r3
	deca r3, r3						;r3 = Última posição do vetor
									;r4 => Posição atual
									;r5, r6, r7 => Registradores temporários para operações

	MAIN:	sub r5, r3, r2			;while(r2 <= r3)
			jt.neg NFOUND

			add r4, r2, r3
			asr r4, r4				;r4 = (r2 + r3) / 2

			passa r5, r0;
			add r5, r5, r4
			load r5, r5				;r5 = VET[r4]

			sub r6, r1, r5			;if(r5 == r1)
			jt.zero END
			nop

			sub r6, r5, r1			;if(r5 < r1)
			jt.neg RIGHT
			nop

			deca r3, r4				;if(r5 > r1)
			j MAIN

	RIGHT: 	inca r2, r4
			j MAIN

	NFOUND: loadlit r4, -1
			j END

	END:	store r10,r4			;Armazena na memória o valor da posicao do elemento

	HALT: j HALT

.dseg
	SIZE: 	.word 10
	ELEM: 	.word 9
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