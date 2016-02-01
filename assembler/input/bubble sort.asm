.module bubble

.pseg
	lcl r0,LOWBYTE VET
    lch r0,HIGHBYTE VET			;Ponteiro para o início do vetor
    load r1,r0					;'r1' recebe a primeira posicao do vetor que contém o número de elementos
    inca r0,r0					;Incrementa r0 para o primeiro elemento a ser ordenado

    passa r1, r1				;r1		x = n
    deca r1, r1                 ;r1     x = n-1
    							;r2		y
    							;r3		temp
    							;r4		temp
    							;r5		temp
    							;r6		temp
	zeros r6					;r6	= 0

    FOR1:	sub r3, r1, r6
    		jt.negzero HALT			;Se x <= 0, finaliza. Se x > 0, executa FOR2

    		zeros r2			;y = 0
    FOR2:	sub r3, r1, r2
    		jt.negzero EFOR1		;Se y >= x, pula p FOR1

    		passa r3, r0		;r3 = &vet[0]
    		add r3, r3, r2		;r3 = &vet[y]
    		load r4, r3			;r4 = vet[y]
    		inca r3, r3			;r3 = &vet[y+1]
    		load r5, r3			;r5 = vet[y+1]
    		sub r7, r5, r4		;r7 = vet[y+1] - vet[y]
    		jt.neg SWAP			;vet[y] > vet[y+1]
    		nop

    EFOR2:	inca r2, r2
    		j FOR2

    SWAP:	store r3, r4
    		deca r3, r3
    		store r3, r5
    		j EFOR2

    EFOR1:	deca r1, r1
    		j FOR1

HALT: j HALT

.dseg

VET:
    	.word   10
            .word   1
            .word   5
            .word   8
            .word   3
            .word   7
            .word   9
            .word   4
            .word   6
            .word   0
            .word   2
.end