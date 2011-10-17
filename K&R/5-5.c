//Mon Sep 27 18:07:20 CST 2010

#include <stdio.h>

static void strncpy1(char *s, const char *t, int n);
static void strncat1(char *s, const char *t, int n);
static int strncmp1(const char *s, const char *t, int n);

int main(void)
{
        char s[10], t[10];
        int n;
        scanf("%s %s %d", s, t, &n);
        strncpy1(s, t, n);
        printf("cpy: %s", s);
        strncat1(s, t, n);
        printf("cat: %s", s);
        printf("cmp: %d", strncmp1(s, t, n));
        return(0);
}

static void strncpy1(char *s, const char *t, int n)
{
        // while ((*s++ = *t++) && --n > 0) not right!
        while (n-- > 0 && (*s++ = *t++))
                ;
        *s = '\0';
}

static void strncat1(char *s, const char *t, int n)
{
        while (*s++)
                ;
        s--;
        while (n-- > 0 && (*s++ = *t++))
                ;
        *s = '\0';
}

static int strncmp1(const char *s, const char *t, int n)
{
        //++ or -- used in a conditional express, should pay attention
        while (n-- > 0 && (*s++ == *t++))
                ;
        return ++n;
}

        
