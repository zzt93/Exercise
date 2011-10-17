/* Mon Sep 20 19:16:20 CST 2010 */
#include <stdio.h>

unsigned int setbits2(unsigned int x, int p, int n, unsigned int y);

int main(void)
{
        unsigned int x, y;
        int p, n;
        scanf("%x %d %d %x", &x, &p, &n, &y);
        printf("%x", setbits2(x,p,n,y));
        return(0);
}

unsigned int setbits2(unsigned int x, int p, int n, unsigned int y)
{                               /* precedence and combine */
              return (x & ~(~0u << sizeof(x) * 8 - n >> sizeof(x) * 8 - n - p )) | \
                      ((y << p) & (~0u << (sizeof(y)*8 - n) >> (sizeof(y)*8 - n - p) ));

}
