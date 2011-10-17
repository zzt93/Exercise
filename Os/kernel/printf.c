#include "type.h"
#include "const.h"
#include "keyboard.h"
#include "tty.h"
#include "console.h"
#include "protect.h"
#include "proc.h"
#include "proto.h"
#include "string.h"

int printf(const char *fmt, ...)
{
        int i;
        char buf[64];
        va_list arg = (va_list)((char *) (&fmt) + 4);
        i = vsprintf(buf, fmt, arg);
        write(buf, i);
        return i;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
        char *p;
        char tmp[64];
        va_list p_next_arg = args;
        
        for (p = buf; *fmt; fmt++) {
                if (*fmt != '%') {
                        *p++ = *fmt;
                        continue;
                }
                
                fmt++;
                
                switch(*fmt) {
                case 'x':
                        itoa(tmp, *((int *) p_next_arg));
                        strcpy(p, tmp);
                        p_next_arg += 4;
                        p += strlen(tmp);
                        break;
                default:
                        break;
                }
        }
        
        return (p - buf);
}
