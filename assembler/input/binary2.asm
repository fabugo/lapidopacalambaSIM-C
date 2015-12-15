.module binary

;Algoritmo de busca binária

.pseg
	lcl	r0, LOWBYTE VET
	lch	r0, HIGHBYTE VET
	loadlit r1,0		;e
	loadlit r2,10		;d
	loadlit r3,5		;x
	;r4 m
	;r5 registrador temporario
	loadlit r6, 1

	MAIN:	sub r5,r2,r1
			jt.neg NOT
			nop

			add r5,r1,r2
			asr r4,r5
			add r0,r0,r4

			sub r5,r0,r3
			jt.zero ENDM
			nop

			jt.neg LEFT
			nop

			deca r2,r4
			j MAIN

	LEFT:	inca r1,r4
			j MAIN

	NOT:	loadlit r5,-1
			j END

	ENDM:	passa r5,r4
			j END

	END:	store r6,r5

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