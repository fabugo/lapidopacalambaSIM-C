.pseg

;Implementacao do algoritmo bubble sort aplicado a um array
;r2 elemento a ordenar ficando na sua posicao final
;r3 para varrer todos os elementos do array

main:       

        lcl r0,LOWBYTE ARR1
        lch r0,HIGHBYTE ARR1
        load r4,r0      
        add r4,r0,r4    
        inca r0,r0      
        passa r1,r0     
        load r2,r0   

LOOP:   inca r1,r1      
        load r3,r1      
        sub r6,r2,r3    
        jt.negzero TROCA
        nop

TROCA:
        store r0,r3     
        store r1,r2    
        passa r5,r2     
        passa r2,r3     
        passa r3,r5   
        j CONT        
        nop

CONT:
        sub r6,r4,r1    
        jf.zero LOOP    
        nop
        sub r6,r4,r0    
        deca r6,r6      
        jt.zero FIM     
        nop
        inca r0,r0      
        load r2,r0      
        passa r1,r0     
        j LOOP
        nop

FIM: j FIM
     nop
.dseg

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
