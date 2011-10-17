//Mon Sep 20 21:14:08 CST 2010

#include <stdio.h>

static unsigned int rightrot(unsigned int x, int n);

int main(void)
{
        unsigned int x;
        int n;
        scanf("%x %d", &x, &n);
        printf("%x", rightrot(x, n));
        return(0);
}

static unsigned int rightrot(unsigned int x, int n)
{
//forget to multiply sizeof(x) with 8...
        return (x >> n) | (x << sizeof(x)*8 - n);
}
