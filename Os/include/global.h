#ifdef GLOBAL_VARIABLES_HERE
#undef EXTERN
#define EXTERN
#endif

EXTERN uint8_t gdt_ptr[6];
EXTERN struct Descriptor gdt[GDT_SIZE];
EXTERN uint8_t idt_ptr[6];
EXTERN struct Gate idt[IDT_SIZE];
EXTERN int disp_pos;

EXTERN struct Task task_table[];
EXTERN struct Task user_proc_table[];
EXTERN struct Process proc_table[];
EXTERN struct Process *proc_ready;
EXTERN struct Tss tss;

EXTERN uint32_t k_reenter;
EXTERN void (*irq_table[])(int);

EXTERN int ticks;

        
extern struct Tty tty_table[];
extern struct Console console_table[];

EXTERN int nr_current_console;






