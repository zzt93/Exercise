//Mon Sep 20 20:44:57 CST 2010

#include <stdio.h>

static unsigned int invert(unsigned int x, int p, int n);
static unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
int main(void)
{
        unsigned int x;
        int p, n;
        scanf("%x %d %d", &x, &p, &n);
        printf("%x", invert(x, p, n));
        return(0);
}

static unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{                               /* precedence and combine */
              return (x & ~(~0u << sizeof(x) * 8 - n >> sizeof(x) * 8 - n - p )) | \
                      (y & (~0u << (sizeof(y)*8 - n) >> (sizeof(y)*8 - n - p) ));
}

static unsigned int invert(unsigned int x, int p, int n)
{
//maybe can be implemented by xor
        return setbits(x,p,n,~x);
}
