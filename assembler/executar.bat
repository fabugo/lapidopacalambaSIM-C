cls
gcc -o assembler assembler.c ../lib/string.c lib/reader.c lib/formatter.c lib/checker.c
assembler "input/teste1.asm" "input/teste2.asm" "input/teste3.asm" "input/fibonacci.asm" "input/binary search.asm" "input/bubble sort.asm" "input/op desvio.asm" "input/op const_desvio_reg.asm" "input/op logica_aritmetica.asm" "input/op memoria.asm"
