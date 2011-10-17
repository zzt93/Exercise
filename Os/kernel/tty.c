#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "keyboard.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"


void tty_write(struct Tty *p_tty, char *buf, int len)
{
        char *p = buf;
        int i = len;
        
        while(i) {
                out_char(p_tty->p_console, *p++);
                i--;
        }
}

int sys_write(char *buf, int len, struct Process *p_proc)
{
        tty_write(&tty_table[p_proc->nr_tty], buf, len);
        return 0;
}

static void init_tty(struct Tty *p_tty)
{
        p_tty->inbuf_count = 0;
        p_tty->head = p_tty->tail = p_tty->in_buf;
        
        init_screen(p_tty);
}

static void tty_do_read(struct Tty *p_tty)
{
        if (p_tty->p_console == &console_table[nr_current_console])
                keyboard_read(p_tty);
}

static void tty_do_write(struct Tty *p_tty)
{
        if (p_tty->inbuf_count) {
                char ch = *(p_tty->tail++);
                if (p_tty->tail == p_tty->in_buf + TTY_IN_BYTES)
                        p_tty->tail = p_tty->in_buf;
                p_tty->inbuf_count--;

                out_char(p_tty->p_console, ch);
        }
}

void task_tty()
{
        struct Tty *p_tty;
        init_keyboard();
        for (p_tty = tty_table; p_tty < tty_table + NR_CONSOLES; p_tty++)
                init_tty(p_tty);
        select_console(0);
        while(1) {
                for (p_tty = tty_table; p_tty < tty_table + NR_CONSOLES; p_tty++) {
                        tty_do_read(p_tty);
                        tty_do_write(p_tty);
                }
        }
}

static void put_key(struct Tty *p_tty, uint32_t key)
{
        if (p_tty->inbuf_count < TTY_IN_BYTES) {
                *(p_tty->head++) = key;
                if (p_tty->head == p_tty->in_buf + TTY_IN_BYTES)
                        p_tty->head = p_tty->in_buf;
                p_tty->inbuf_count++;
        }
}


void in_process(struct Tty *p_tty, uint32_t key)
{

        if (!(key & FLAG_EXT)) {
                put_key(p_tty, key);
                
        } else {
                int raw_code = key & MASK_RAW;
                switch(raw_code) {
                case ENTER:
                        put_key(p_tty, 0x0a);
                        break;
                case BACKSPACE:
                        put_key(p_tty, '\b');
                        break;
                case UP:
                        if ((key & FLAG_SHIFT_L) || (key & FLAG_SHIFT_R))
                                scroll_screen(p_tty->p_console, SCR_DN);
                        break;
                case DOWN:
                        if ((key & FLAG_SHIFT_L) || (key & FLAG_SHIFT_R))
                                scroll_screen(p_tty->p_console, SCR_UP);
                        break;
                case F1:
                case F2:
                case F3:
                case F4:
                case F5:
                case F6:
                case F7:
                case F8:
                case F9:
                case F10:
                case F11:
                case F12:
                        /* Alt + F1~F12 */
                        if ((key & FLAG_SHIFT_L) || (key & FLAG_SHIFT_R)) {
                                select_console(raw_code - F1);
                        }
                        break;
                default:
                        break;
                }
        }

}
