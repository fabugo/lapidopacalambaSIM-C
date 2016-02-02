.module Operações de Memória
.pseg
			loadlit r0, 0
			loadlit r1, 5
			loadlit r2, 10

			loadlit r3, 11
			loadlit r4, 2
			loadlit r5, 7

			store r0, r3
			store r1, r4
			store r2, r5

			load r6, r0
			load r7, r1
			load r8, r2

			sub r3, r3, r6
			jf.zero FAIL			;Se 'r3 != r6', o valor será diferente de 0

			sub r4, r4, r7
			jf.zero FAIL			;Se 'r4 != r7', o valor será diferente de 0

			sub r5, r5, r8
			jf.zero FAIL			;Se 'r5 != r8', o valor será diferente de 0

			j END

	FAIL: 	j FAIL					;Se cair nesse halt (Instrução 20), não funciona corretamente

	END: 	j END 					;Se cair nesse halt (Instrução 21) e 'r3 = r4 = r5 = 0', o teste passou
.end