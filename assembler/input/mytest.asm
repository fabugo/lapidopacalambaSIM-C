.module binary
.pseg

HALT: 	lcl r0, LOWBYTE 123
		lch r0, HIGHBYTE 123
		lcl r1, LOWBYTE 0
		lch r1, HIGHBYTE 0
		store r1,r0
		j HALT

.dseg
TESTE: 	.word 10
		.word 15
		.word 14
		.word 18
		.word 154
		.word 44
		.word 37
		.word 123
		.word 14
		.word 16
		.word 17
.end