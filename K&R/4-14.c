//Mon Sep 27 14:42:24 CST 2010

#include <stdio.h>
//good method!
#define swap(t, a, b)                           \
        {                                       \
                t x; x = a; a = b; b = x;       \
        }

int main(void)
{
        double a = 444, b = 555;
        swap(double, a, b);
        printf("%f %f", a, b);
        return(0);
}
