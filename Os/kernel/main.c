#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"
#include "string.h"


char task_stack[STACK_TOTAL_SIZE];

void TestA()
{
        while(1){
                printf("<Ticks:%x>", get_ticks());
                delay(200);
        }
}

void TestB()
{
        while(1) {
                printf("B");
                delay(1000);
        }
}


void TestC()
{
        while(1) {
                printf("C");
                delay(1000);
        }
}



void tinix_main()
{
        disp_str("------------\"tinix_main\" begins-----------\n");

        struct Process *proc = proc_table;
        char *pstack = task_stack + STACK_TOTAL_SIZE; 
        int i;
        
        for (i = 0; i < NR_TASKS + NR_PROCS; i++, pstack -= (i < NR_TASKS ? task_table[i] : user_proc_table[i - NR_TASKS]).stacksize, proc++) {
                
                proc->ldt_sel = SELECTOR_LDT_FIRST + 8 * i;
                
                memcpy(&proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3], sizeof(struct Descriptor));
                proc->ldts[0].attr1 = DA_C | (i < NR_TASKS ? PRIVILEGE_TASK : PRIVILEGE_USER) << 5;
                memcpy(&proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3], sizeof(struct Descriptor));
                proc->ldts[1].attr1 = DA_DRW | (i < NR_TASKS ? PRIVILEGE_TASK : PRIVILEGE_USER) << 5;
                
                proc->regs.cs = ((0 << 3) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | (i < NR_TASKS ? RPL_TASK : RPL_USER);
                proc->regs.ds = ((1 << 3) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | (i < NR_TASKS ? RPL_TASK : RPL_USER);
                proc->regs.es = ((1 << 3) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | (i < NR_TASKS ? RPL_TASK : RPL_USER);
                proc->regs.fs = ((1 << 3) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | (i < NR_TASKS ? RPL_TASK : RPL_USER);
                proc->regs.ss = ((1 << 3) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | (i < NR_TASKS ? RPL_TASK : RPL_USER);
                proc->regs.gs = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | (i < NR_TASKS ? RPL_TASK : RPL_USER);
                
                proc->regs.eip = (uint32_t)(i < NR_TASKS ? task_table[i].initial_eip : user_proc_table[i - NR_TASKS].initial_eip);
                proc->regs.esp = (uint32_t)pstack; 
                proc->regs.eflags = i < NR_TASKS ? 0x1202 : 0x202;
                proc->nr_tty = 0;

        }
        k_reenter = 0;
        
        proc_ready = proc_table;

        init_clock();

        proc_table[0].ticks = proc_table[0].priority = 30;
        proc_table[1].ticks = proc_table[1].priority = 15;
        proc_table[2].ticks = proc_table[2].priority = 15;
        proc_table[3].ticks = proc_table[3].priority = 15;
        
        proc_table[1].nr_tty = 0;
        proc_table[2].nr_tty = 1;
        proc_table[3].nr_tty = 1;


        ticks = 0;
        
        restart();
        

}

