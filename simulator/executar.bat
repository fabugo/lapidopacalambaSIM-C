cls
gcc -o processor processor.c ../lib/string.c modules/program_counter.c modules/memory_instruction.c modules/signal_extender.c modules/register_bank.c modules/data_memory.c modules/alu.c modules/register_flags.c modules/tester_flags.c modules/unit_control.c modules/mx_pc.c modules/mx_rb.c modules/mx_se.c
processor