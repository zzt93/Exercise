#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

void cstart()
{
        memcpy(&gdt, (void *)(*((uint32_t *)(&gdt_ptr[2]))), *((uint16_t*)(&gdt_ptr[0])) + 1);
        
        *((uint32_t *)(&gdt_ptr[2])) = (uint32_t)&gdt;
        *((uint16_t *)(&gdt_ptr[0])) = GDT_SIZE * sizeof(struct Descriptor) - 1;

        *((uint32_t *)(&idt_ptr[2])) = (uint32_t)&idt;
        *((uint16_t *)(&idt_ptr[0])) = IDT_SIZE * sizeof(struct Gate) - 1;

        init_prot();
        
        disp_str("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n--------------\"cstart\"  begins---------------\n");

        return;
}

        
