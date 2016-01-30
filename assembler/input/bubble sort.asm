;Implementação do algoritmo bubble sort.
;Foi baseado na seguinte implementação na linguagem C:
	;int n = 10;
	;int vet[] = {10,4,8,7,3,9,5,2,6,1};
	;int x, y;
	;for(x = n; x > 0; x--){
	;	for(y = 0; y < x; y++){
	;		if(vet[y] > vet[y + 1]){
	;			vet[y] += vet[y+1]; 
	;			vet[y+1] = vet[y] - vet[y+1];
	;			vet[y] -= vet[y+1];
	;		}
	;	}
	;}

.module bubble

.pseg
	lcl r0,LOWBYTE VET
    lch r0,HIGHBYTE VET			;Ponteiro para o início do vetor
    load r1,r0					;'r1' recebe a primeira posicao do vetor que contém o número de elementos
    inca r0,r0					;Incrementa r0 para o primeiro elemento a ser ordenado

    passa r2, r1				;r2		x = n
    							;r3		y
    							;r4		temp
    							;r5		temp
    							;r6		temp
    							;r8		temp
	zeros r8					;r8	= 0

    FOR1:	sub r4, r8, r2
    		jf.neg HALT			;Se x <= 0, finaliza. Se x > 0, executa FOR2

    		zeros r3			;y = 0
    FOR2:	sub r4, r3, r2
    		jf.neg EFOR1		;Se y >= x, pula p FOR1

    		passa r4, r0		;r4 = &vet[0]
    		add r4, r4, r3		;r4 = &vet[y]
    		load r5, r4			;r5 = vet[y]
    		inca r4, r4			;r4 = &vet[y+1]
    		load r6, r4			;r6 = vet[y+1]
    		sub r7, r6, r5		;r7 = vet[y+1] - vet[y]
    		jt.neg SWAP			;vet[y] > vet[y+1]
    		nop

    EFOR2:	inca r3, r3
    		j FOR2

    SWAP:	store r4, r5
    		deca r4, r4
    		store r4, r6
    		j EFOR2

    EFOR1:	deca r2, r2
    		j FOR1

HALT: j HALT

.dseg

VET:
    	.word   10
            .word   7
            .word   5
            .word   2
            .word   1
            .word   -1
            .word   0
            .word   8
            .word   4
            .word   3
            .word   6
.end