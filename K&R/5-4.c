//Mon Sep 27 17:11:19 CST 2010

#include <stdio.h>

static int strend(const char *s, const char *t);


int main(void)
{
        char s[10], t[10];
        scanf("%s %s", s, t);
        printf("%d", strend(s, t));
        return(0);
}

static int strend(const char *s, const char *t)
{
        char *p;
        p = t;
        while (*s++)
                ;
        while (*t++)
                ;
//not very familiar
        for (s--, t--; *t == *s && t >= p; t--, s--)
                ;
        if (t < p)
                return(1);
        else
                return(0);
}

                
