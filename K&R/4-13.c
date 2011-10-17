//Mon Sep 27 13:19:32 CST 2010

#include <stdio.h>
#include <string.h>

static void reverse(char *s);

int main(void)
{
        char a[20];
        scanf("%s", a);
        reverse(a);
        printf("\n%s", a);
        return(0);
}

static void reverse(char *s)
{
        static int len;
        static int pos = 0;
        len = strlen(s) - 1;
        char t;
        //not very good, hard to read!
        if (pos == (len + pos + 1)/2)
                return;
        else {
                t = *s;
                *s = s[len - pos];
                s[len - pos] = t;
                pos++;
                reverse(s + 1);
        }
}
