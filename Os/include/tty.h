#ifndef _XXX_TTY_H_
#define _XXX_TTY_H_

#define TTY_IN_BYTES	256	/* tty input queue size */

struct Tty {
        uint32_t in_buf[TTY_IN_BYTES];
        uint32_t *head;
        uint32_t *tail;
        int inbuf_count;
        struct Console *p_console;
};

#endif
        
        
