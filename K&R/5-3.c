//Mon Sep 27 16:57:46 CST 2010

#include <stdio.h>

static void strcat1(char *s, const char *t);

int main(void)
{
        char s[10], t[10];
        scanf("%s %s", s, t);
        strcat1(s, t);
        printf("%s", s);
        return(0);
}

static void strcat1(char *s, const char *t)
{
//mistake again!!!!!!!!!!!!!!!!!!
        while (*s++)
                ;
        s--;
        while (*s++ = *t++)
                ;
}
