.module Fibonacci 
.pseg 
	loadlit r0, 10
	loadlit r1, 1
	loadlit r2, 1
	loadlit r5, 1023
	loadlit r6, 6
	nop
Label1: add r4,r2,r1
	passa r1,r2
	passa r2,r4
	deca r0,r0
	jt.zero Label2 
	nop
	jal r6
	nop
Label2:	store r5,r4
Label3:	j Label3
	nop
.dseg

.end
