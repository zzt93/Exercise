//Thu Sep 30 00:57:29 CST 2010
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20
#define MAXLEN 10

static void qsort1(void *s[], int start, int end, \
                   int (*cmp)(void *, void *));

static int numcmp(char *, char *);

//static void swap(void *s[], void *, void *); will not work

static void swap(void *s[], int, int);

static int reverse;

int main(int argc, char *argv[])
{
        char *ch[MAX];
        int c;
        int number = 0;
        for (int i = 0; i < MAX; i++) {
                ch[i] = malloc(sizeof(char) * MAXLEN);
                sprintf(ch[i], "%d", i + 0);
        }
        while (--argc > 0 && (*++argv)[0] == '-')
                while ((c = *++argv[0]) != '\0')
                        switch (c) {
                        case 'n':
                                number = 1;
                                break;
                        case 'r':
                                reverse = 1;
                                break;
                        default:
                                printf("illegal option %c\nusage: a.out -x -n pattern\n", c);
                                return(0);
                                break;
                        }
        if (argc != 0) {
                printf("usage: a.out -x -n pattern\n");
                return(0);
        }
        qsort1((void*)ch, 0, MAX - 1, \
               ((number) ? \
                (int (*)(void*,void*)) numcmp : \
                (int (*)(void*,void*)) strcmp));
        for (int i = 0; i < MAX; i++)
                printf("%s ", ch[i]);
        putc('\n', stdout);
        return(0);
}

static int numcmp(char *a, char *b)
{
        double aa, bb;
        if ((aa = atof(a)) < (bb = atof(b)))
                return -1;
        else if (aa > bb)
                return 1;
        else return 0;
}

static void swap(void *s[], int i, int j)
{
        void *tmp;
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
}


static void qsort1(void *s[], int start, int end, \
                   int (*cmp)(void *a, void *b))
{
        int pos;
        if (end <= start)
                return;
        swap(s, start, (start + end) / 2);
        pos = start;
        for (int i = start + 1; i <= end; i++)
                if (((reverse) ? -cmp(s[i], s[start]) : cmp(s[i], s[start])) > 0)
                        swap(s, i, ++pos);
        //swap(s, s[pos], s[start]) will not work
        swap(s, pos, start);
        qsort1((void*)s, start, pos - 1, (int (*)(void*,void*))cmp);
        qsort1((void*)s, pos + 1, end, (int (*)(void*,void*))cmp);
}

        

