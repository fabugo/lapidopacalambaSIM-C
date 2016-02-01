.module Operações de desvio (jt, jf, j)
.pseg

			jt.true ONE
			j FAIL

	ONE:	loadlit r0, 5
			loadlit r1, 10
			loadlit r2, 15
			jf.true FAIL
			j THREE

	TWO:	sub r1, r1, r1
			jt.zero FOUR
			j FAIL

	THREE:	sub r3, r2, r1
			jf.zero TWO
			j FAIL

	FOUR:	sub r3, r0, r2
			jt.neg SIX
			j FAIL

	FIVE:	zeros r0
			sub r2, r2, r2
			jt.negzero END
			j FAIL
	SIX:	sub r0, r0, r2
			jf.neg FAIL
			j FIVE


	FAIL: 	j FAIL					;Se cair nesse halt (Instrução 21), não funciona corretamente

	END: 	j END 					;Se cair nesse halt (Instrução 25) e 'r0 = r1 = r2 = 0', o teste passou
.end