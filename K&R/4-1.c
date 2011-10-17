//Tue Sep 21 23:03:29 CST 2010

#include <stdio.h>
#define MAX 30

static int strrindex(const char *s, const char *t);

int main(void)
{
        char s[MAX],t[MAX];
        scanf("%s %s", s, t);
        printf("%d", strrindex(s, t));
        return(0);
}

static int strrindex(const char *s, const char *t)
{
        int i, j, k, pos = -1;
        for (i = 0; s[i] != '\0'; i++) {
                for (j = 0, k = i; s[k] == t[j] && t[j] != '\0'; j++, k++)
                        ;
                //j > 0 to ensure t is not a null string
                if (j > 0 && t[j] == '\0')
                        pos = i;
        }
        return pos;
}

                        
