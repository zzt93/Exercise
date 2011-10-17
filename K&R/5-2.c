//Mon Sep 27 15:54:46 CST 2010

#include <stdio.h>
#include <ctype.h>

static int getfloat(float *p);


int main(void)
{
        float f;
        float *pf;
        pf = &f;
        while (getfloat(pf) != EOF)
                printf("%f", *pf);
        return(0);
}
//lost some precise...
static int getfloat(float *p)
{
        int c, sign;
        float frac = 0, pow = 1;
        while (isspace(c = getc(stdin)))
                ;
        if (!isdigit(c) && c != '+' && c != '-' && c != '.' && c != EOF) {
                ungetc(c, stdin);
                return(0);
        }
        sign = (c == '-') ? -1 : 1;
        if (c == '-' || c == '+' || c == '.') {
                int t = c;
                c = getc(stdin);
                if (!isdigit(c)) {
                        ungetc(c, stdin);
                        ungetc(t, stdin);
                        return(0);
                }
        }
        for (*p = 0; isdigit(c); c = getc(stdin))
                *p = *p * 10 + (c - '0');
        if (c == '.') 
                while (isdigit(c = getc(stdin))) {
                        frac = frac * 10 + (c - '0');
                        pow *= 10;
                }
        *p += frac / pow;
        *p *= sign;
        if (c != EOF)
                ungetc(c, stdin);
        return c;
}

                        
