#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"


struct Task task_table[NR_TASKS] = {
        {task_tty, STACK_SIZE_TESTA, "tty"}
};

struct Task user_proc_table[NR_PROCS] = {
        {TestA, STACK_SIZE_TESTA, "TestA"},
        {TestB, STACK_SIZE_TESTB, "TestB"},
        {TestC, STACK_SIZE_TESTC, "TestC"}
};
                

struct Process proc_table[NR_TASKS + NR_PROCS];

void (*irq_table[NR_IRQ])(int irq);

void *sys_call_table[NR_SYS_CALL] = {sys_get_ticks, sys_write};

        
struct Tty tty_table[NR_CONSOLES];
struct Console console_table[NR_CONSOLES];






