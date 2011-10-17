#include "type.h"
#include "const.h"
#include "keyboard.h"
#include "keymap.h"
#include "tty.h"
#include "console.h"
#include "protect.h"
#include "proc.h"
#include "proto.h"


static struct Kb_input kb_in;
static int code_with_E0;
static int shift_l, shift_r, ctrl_l, ctrl_r, alt_l, alt_r;


void keyboard_handler(int irq)
{
        uint8_t scan_code = in_byte(KB_DATA);
        
        if (kb_in.count < KB_IN_BYTES) {
                *(kb_in.head) = scan_code;
                kb_in.head++;
                if (kb_in.head == kb_in.buf + KB_IN_BYTES)
                        kb_in.head = kb_in.buf;
                kb_in.count++;
        }
        
}

void init_keyboard()
{
        shift_l	= shift_r = 0;
        alt_l	= alt_r   = 0;
        ctrl_l	= ctrl_r  = 0;
        code_with_E0 = 0;
        
        kb_in.count = 0;
        kb_in.head = kb_in.tail = kb_in.buf;
        put_irq_handler(KEYBOARD_IRQ, keyboard_handler);
        enable_irq(KEYBOARD_IRQ);
}

static uint8_t get_byte_from_kb_buf()
{
        uint8_t scan_code;
        
        while (kb_in.count <= 0)
                ;
        disable_int();
        scan_code = *(kb_in.tail);
        kb_in.tail++;
        if (kb_in.tail == kb_in.buf + KB_IN_BYTES)
                kb_in.tail = kb_in.buf;
        kb_in.count--;
        enable_int();
        return scan_code;
}

        
void keyboard_read(struct Tty *p_tty)
{
        uint8_t scan_code;
        int key = 0;
        int make;
        int column;
        
        if (kb_in.count > 0) {
                code_with_E0 = 0;
                scan_code = get_byte_from_kb_buf();
                
                if(scan_code == 0xe1) {
                        int i;
                        uint8_t pausebreak_scan_code[] = {0xe1, 0x1d, 0x45, 0xe1, 0x9d, 0xc5};
                        int is_pausebreak = 1;
                        for (i = 1; i < 6; i++)
                                if (get_byte_from_kb_buf() != pausebreak_scan_code[i]) {
                                        is_pausebreak = 0;
                                        break;
                                }
                        if (is_pausebreak)
                                key = PAUSEBREAK;

                } else if (scan_code == 0xe0) {

                        scan_code = get_byte_from_kb_buf();
                        if (scan_code == 0x2a)
                                if (get_byte_from_kb_buf() == 0xe0)
                                        if (get_byte_from_kb_buf() == 0x37) {
                                                key = PRINTSCREEN;
                                                make = 1;
                                        }
                        if (scan_code == 0xb7)
                                if (get_byte_from_kb_buf() == 0xe0)
                                        if (get_byte_from_kb_buf() == 0xaa) {
                                                key = PRINTSCREEN;
                                                make = 0;
                                        }
                        if (key == 0)
                                code_with_E0 = 1;
                }

                if ((key != PAUSEBREAK) && (key != PRINTSCREEN)) {

                        make = (scan_code & FLAG_BREAK ? 0 : 1);
                        column = 0;
                        
                        if (shift_l || shift_r)
                                column = 1;
                        
                        if (code_with_E0) {
                                column = 2;
                                code_with_E0 = 0;
                        }
                        key = keymap[(scan_code & 0x7f) * MAP_COLS + column];                        
                        switch(key) {
                        case SHIFT_L:
                                shift_l = make;
                                break;
                        case SHIFT_R:
                                shift_r = make;
                                break;
                        case CTRL_L:
                                ctrl_l = make;
                                break;
                        case CTRL_R:
                                ctrl_r = make;
                                break;
                        case ALT_L:
                                alt_l = make;
                                break;
                        case ALT_R:
                                alt_r = make;
                                break;
                        default:
                                break;
                        }
                        
                        if (make) {
                                key |= shift_l	? FLAG_SHIFT_L	: 0;
                                key |= shift_r	? FLAG_SHIFT_R	: 0;
                                key |= ctrl_l	? FLAG_CTRL_L	: 0;
                                key |= ctrl_r	? FLAG_CTRL_R	: 0;
                                key |= alt_l	? FLAG_ALT_L	: 0;
                                key |= alt_r	? FLAG_ALT_R	: 0;
			
                                in_process(p_tty, key);
                        }
                }
        }
}
