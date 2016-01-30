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
        lch r0,HIGHBYTE VET		;Ponteiro para o início do vetor
        load r1,r0				;'r1' recebe a primeira posicao do vetor que contém o número de elementos
        inca r0,r0				;Incrementa r0 para o primeiro elemento a ser ordenado
        
        passa r2,r1				;'r2' recebe o tamanho do vetor
		loadlit r3,-1			;'r3' registrador auxiliar para percorrer o vetor. Na primeira execução
								;ele terá o valor 0. "inca r3,r3"
		
		;'r4' registrador temporário para operações
		;'r5' registrador temporário para operações
		;'r6' registrador temporário para operações

LOOP1:	deca r2,r2				;'r2' inicia na ultima posição do vetor ('r1'-1) e é decrementado até 0
		jt.zero HALT  	 		;Se r2 == 0, encerra
		nop

LOOP2:  inca r3,r3
		sub r4,r2,r3			;Operação para teste com flags		
		jt.negzero LOOP1		;Se r3 >= r2, volta para o primeiro loop
		nop

		;Se r3 < r2, verifica se vet[r3] > vet['r3'+1]
		add r6,r0,r3
		load r4, r6				;'r4' = vet['r3']
		inca r6,r6
		load r5,r6				;'r5' = vet['r3'+1]

		sub r6,r5,r4			;Operação para teste com flags
		jf.neg LOOP2			;Se r4 <= r5
		nop

		;Se r4 > r5, troca as posições dos dois valores no vetor
		add r6,r0,r3
		store r6,r5
		inca r6,r6
		store r6,r4

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