#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

void init_8259A()
{
        out_byte(INT_M_CTL, 0x11);
        out_byte(INT_S_CTL, 0x11);
        
        out_byte(INT_M_CTLMASK, INT_VECTOR_IRQ0);
        out_byte(INT_S_CTLMASK, INT_VECTOR_IRQ8);
        
        out_byte(INT_M_CTLMASK, 0x4);
        out_byte(INT_S_CTLMASK, 0x2);
        
        out_byte(INT_M_CTLMASK, 0x1);
        out_byte(INT_S_CTLMASK, 0x1);

        /* 屏蔽主从8259中断 */
        out_byte(INT_M_CTLMASK, 0xff);
        out_byte(INT_S_CTLMASK, 0xff);
        
        int i;
        for (i = 0; i < NR_IRQ; i++) 
                irq_table[i] = spurious_irq;
}

void spurious_irq(int irq)
{
        disp_str("spurious_irq: ");
        disp_int(irq);
        disp_str("\n");
}

void put_irq_handler(int irq, void (*handler)(int))
{
        disable_irq(irq);
        irq_table[irq] = handler;
}
