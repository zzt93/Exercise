//Mon Sep 27 18:59:14 CST 2010

#include <stdio.h>
#define MAXLINE 100
#define MAXLEN 100

//readlines(char *a[]) is wrong!!!!!!!!!!!!!
static int readlines(char a[][MAXLEN]);
static int getline(char a[], int len);

int main(void)
{
        char a[MAXLINE][MAXLEN]={0};
        int line;
        line = readlines(a);
        for (; line >= 0; line--)
                printf("%s", a[line]);
        return(0);
}

static int readlines(char a[][MAXLEN])
{
        int line = 0;
        while (line < MAXLINE && getline(a[line++], MAXLEN) > 0)
                ;
        return line;
}

static int getline(char a[], int len)
{
        int ch, i = 0;
        //should remember
        while (i < len-1 && (ch = getc(stdin)) != '\n' && ch != EOF)
                a[i++] = ch;
        a[i] = '\0';
        return ch;
}
