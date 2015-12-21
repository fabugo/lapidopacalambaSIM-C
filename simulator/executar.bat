cls
gcc -o processor processor.c ../lib/string.c modules/program_counter.c modules/memory_instruction.c modules/register_bank.c modules/data_memory.c
processor
