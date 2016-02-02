.module Operações Lógicas e Aritméticas
.pseg
			loadlit r0, 1
			loadlit r1, 3
			loadlit r2, 2
			loadlit r3, 4

			loadlit r4, 5
			loadlit r5, 8
			loadlit r6, -3
			loadlit r7, 3
			loadlit r8, 13


			add r9, r0, r1
			sub r9, r9, r3
			jf.zero FAIL

			addinc r9, r4, r2
			passa r10, r5
			sub r10, r9, r10
			jf.zero FAIL

			inca r10, r10
			deca r10, r10
			jf.zero FAIL

			passb r10, r8
			zeros r10
			jf.zero FAIL

			passb r9, r3
			subdec r9, r3, r1
			jf.zero FAIL

			lsl r0, r0
			asr r0, r0
			and r0, r1, r2
			andnota r0, r1, r2
			passb r0, r0
			andnotb r0, r1, r2
			xor r0, r1, r2
			or r0, r1, r2
			nand r0, r1, r2
			xnor r0, r1, r2
			passnota r0, r1
			ornota r0, r1, r2
			passnotb r0, r1
			ornotb r0, r1, r2
			nor r0, r1, r2
			ones r0
			j END


	FAIL: j FAIL					;Se cair nesse halt (Instrução 42), não funciona corretamente

	END: j END 						;Se cair nesse halt (Instrução 43), o teste passou
.end