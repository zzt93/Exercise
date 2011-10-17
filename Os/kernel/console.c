#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "keyboard.h"
#include "proto.h"

static void set_video_start_addr(uint32_t addr)
{
        disable_int();
        out_byte(CRTC_ADDR_REG, START_ADDR_H);
        out_byte(CRTC_DATA_REG, (addr >> 8) & 0xFF);
        out_byte(CRTC_ADDR_REG, START_ADDR_L);
        out_byte(CRTC_DATA_REG, addr & 0xFF);
        enable_int();
}





static void set_cursor(unsigned int position)
{
        disable_int();
        out_byte(CRTC_ADDR_REG, CURSOR_H);
        out_byte(CRTC_DATA_REG, (position >> 8) & 0xFF);
        out_byte(CRTC_ADDR_REG, CURSOR_L);
        out_byte(CRTC_DATA_REG, position & 0xFF);
        enable_int();
}

static void flush(struct Console *p_con)
{
        if (p_con == &console_table[nr_current_console]) {
                
                set_cursor(p_con->cursor);
                set_video_start_addr(p_con->current_start_addr);
        }
}


void out_char(struct Console *p_con, char ch)
{
        uint8_t *p_vmem = (uint8_t *) (V_MEM_BASE + p_con->cursor * 2);

        switch(ch) {
        case '\n':
                if (p_con->cursor < p_con->original_addr + p_con->v_mem_limit - SCREEN_WIDTH)
                        p_con->cursor = p_con->original_addr + SCREEN_WIDTH * ((p_con->cursor - p_con->original_addr)/SCREEN_WIDTH + 1);
                break;
        case '\b':
                if (p_con->cursor > p_con->original_addr) {
                        p_con->cursor--;
                        *(p_vmem-2) = ' ';
                        *(p_vmem-1) = DEFAULT_CHAR_COLOR;
                }
                break;
        default:
                if (p_con->cursor < p_con->original_addr + p_con->v_mem_limit - 1) {
                        *p_vmem++ = ch;
                        *p_vmem++ = DEFAULT_CHAR_COLOR;
                        p_con->cursor++;
                }
                break;
        }
        
        while (p_con->cursor >= p_con->current_start_addr + SCREEN_SIZE)
                scroll_screen(p_con, SCR_DN);

        flush(p_con);
        
}

void init_screen(struct Tty *p_tty)
{
        int nr_tty = p_tty - tty_table;
        p_tty->p_console = console_table + nr_tty;
        
        int v_mem_size = V_MEM_SIZE >> 1;
        int con_v_mem_size = v_mem_size / NR_CONSOLES;
        
        p_tty->p_console->original_addr = nr_tty * con_v_mem_size;
        p_tty->p_console->v_mem_limit = con_v_mem_size;
        p_tty->p_console->current_start_addr = p_tty->p_console->original_addr;
        p_tty->p_console->cursor = p_tty->p_console->original_addr;
        
        if (nr_tty == 0)
                p_tty->p_console->cursor = disp_pos/2;
        else {
                out_char(p_tty->p_console, nr_tty + '0');
                out_char(p_tty->p_console, '#');
        }
        
        set_cursor(p_tty->p_console->cursor);
}


void select_console(int nr_console)	/* 0 ~ (NR_CONSOLES - 1) */
{
        if ((nr_console < 0) || (nr_console >= NR_CONSOLES)) {
                return;
        }

        nr_current_console = nr_console;
	flush(&console_table[nr_console]);
}


void scroll_screen(struct Console* p_con, int direction)
{
        if (direction == SCR_UP) {
	
                if (p_con->current_start_addr > p_con->original_addr)
                        p_con->current_start_addr -= SCREEN_WIDTH;

        } else if (direction == SCR_DN) {

                if (p_con->current_start_addr + SCREEN_SIZE < p_con->original_addr + p_con->v_mem_limit) 
                        p_con->current_start_addr += SCREEN_WIDTH;

        }
	flush(p_con);
}

