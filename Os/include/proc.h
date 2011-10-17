#ifndef _XXX_PROC_H_
#define _XXX_PROC_H_

#define NR_TASKS 1
#define NR_PROCS 3

struct Stackframe {
        uint32_t gs;
        uint32_t fs;
        uint32_t es;
        uint32_t ds;
        uint32_t edi;
        uint32_t esi;
        uint32_t ebp;
        uint32_t kernel_esp;
        uint32_t ebx;
        uint32_t edx;
        uint32_t ecx;
        uint32_t eax;
        uint32_t retaddr;
        uint32_t eip;
        uint32_t cs;
        uint32_t eflags;
        uint32_t esp;
        uint32_t ss;
};

struct Process {
        struct Stackframe regs;
        uint16_t ldt_sel;
        struct Descriptor ldts[LDT_SIZE];
        int ticks;
        int priority;
        uint32_t pid;
        char p_name[16];
        int nr_tty;
};

struct Task {
        void (*initial_eip)();
        int stacksize;
        char name[32];
};

        
#endif        
        
        
