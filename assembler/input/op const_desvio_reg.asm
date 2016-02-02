.module Operações de Desvio por Registrador (jal, jr)
.pseg
			loadlit r1, 20			;r1 = 20
			loadlit r2, 12			;r2 = 12
			
			lcl r0, LOWBYTE ADD
			lch r0, HIGHBYTE ADD
			jal r0

			sub r3,r3,r1			;r3 = r3 - r1 = 12
			sub r3,r3,r2			;r3 = r3 - r2 = 0
			
			lcl r0, LOWBYTE END
			lch r0, HIGHBYTE END
			jr r0

	ADD:	add r3, r1, r2			;r3 = r1 + r2 = 32
			jr r15
			j FAIL

	FAIL: j FAIL					;Se cair nesse halt (Instrução 30), não funciona corretamente

	END: j END 						;Se cair nesse halt (Instrução 31) e 'r3 = 0', o teste passou
.end