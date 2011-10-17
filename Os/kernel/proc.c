
#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

int sys_get_ticks()
{
        return ticks;
}

void schedule()
{
        struct Process *p;
        int greatest_ticks = 0;
        while (!greatest_ticks) {
                for (p = proc_table; p < proc_table + NR_TASKS + NR_PROCS; p++)
                        if (p->ticks > greatest_ticks) {
                                greatest_ticks = p->ticks;
                                proc_ready = p;
                        }
                if (!greatest_ticks)
                        for (p = proc_table; p < proc_table + NR_TASKS + NR_PROCS; p++)
                                p->ticks = p->priority;
        }
}

