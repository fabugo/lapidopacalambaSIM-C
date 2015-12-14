;for(i = 0; i<5; i++){
;		for(int j = 0; j<4; j++){
;			if(vet[j] > vet[j + 1]){
;				aux = vet[j]; 
;				vet[j] = vet[j+1];
;				vet[j+1] = aux;
;			}
;		}
;	}

;r4 tamanho do vetor, r0 == i e r1 == j

main:   

		lcl r0,LOWBYTE ARR1
        lch r0,HIGHBYTE ARR1
        load r4,r0           ;r4 tem o numero de elementos que constituem o array


		zeros r0 		     ;i=0

LOOP1:	sub r5,r0,r4         ;i<=n r5 nâo é utilizado apenas interessa o resultado presente à saida da ALU para as flags ()
		jf.negzero EXIT  	 ;r0>=r4 

		zeros r1    		 ;atribui 0 ao registrador r0, j=0
		deca r3, r4 		 ;j=r4-1

LOOP2:  sub r5,r1,r3 		 ;j<=n-1 r5 nâo é utilizado apenas interessa o resultado presente à saida da ALU para as flags ()
		jf.negzero EXITLOOP2  	 ;r0>=r4

		inca r6, r1			 ;guardo em r6 j+1
		load r7, r1			 ;guardo v[j]
		load r8, r6			 ;guardo v[j+1]
		sub r6, r7,r8        ;se v[j]>v[j+1]
		jt.negzero LOOP2
		passa r9, r7         ;aux = vet[j];
		passa r7, r8         ;vet[j] = vet[j+1]
		passa r8, r9		 ;vet[j+1] = aux;

		inca r1, r1 		 ;j+=1
		j LOOP2              ;salta para o loop interno
		

EXITLOOP2: 	inca r0, r0 	 ; i+=1
			j LOOP1          ; salta para o loop externo

EXIT:   	j EXIT


ARR1:
      .word   10
            .word   -1
            .word   6
            .word   3
            .word   -2
            .word   4
            .word   0
            .word   -3
            .word   5
            .word   1
            .word   2
STACK:
.end


