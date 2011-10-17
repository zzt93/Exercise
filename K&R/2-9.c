//Mon Sep 20 21:37:51 CST 2010

#include <stdio.h>
//I still don't know why the book says 'in two's complement system'
static int bitcount(unsigned x);

int main(void)
{
        unsigned int x;
        scanf("%d", &x);
        printf("%d", bitcount(x));
        return(0);
}
//good algorithm, can be used in CRC
static int bitcount(unsigned x)
{
        int i;
        for (i = 0; x; i++)
                x &= x-1;
        return i;
}
//also good algorithm, 判断一个数(x)是否是2的n次方
int func(int x)
{
    if( (x&(x-1)) == 0 )
        return 1;
    else
        return 0;
}
