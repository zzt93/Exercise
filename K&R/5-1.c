//Mon Sep 27 15:15:56 CST 2010

#include <stdio.h>
#include <ctype.h>

static int getch(void);
static void ungetch(int);
static int getint(int *pn);

int main(void)
{
        //int *p = 0 illeagal!!!!
        int a = 10;
        int *p;
        p = &a;
        while (getint(p) != EOF)
                printf("%d", *p);
        return(0);
}

static int getint(int *pn)
{
        int c, t, sign;
        while (isspace(c = getch()))
                ;
        if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
                ungetch(c);
                return(0);
        }
        sign = (c == '-') ? -1 : 1;
        if (c == '-' || c == '+') {
                t = c;
                c = getch();
                if(!isdigit(c)) {
                        ungetch(c);
                        ungetch(t);
                        return(0);
                }
        }
        for (*pn = 0; isdigit(c); c = getch())
                *pn = 10 * *pn + (c - '0');
        *pn *= sign;
        if (c != EOF)
                ungetch(c);
        return c;
}

#define BUFSIZE 2
char buf[BUFSIZE];
int bufp;

static int getch(void)
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

static void ungetch(int c)
{
        if (bufp > BUFSIZE)
                printf("buf full!\n");
        else
                buf[bufp++] = c;
}
