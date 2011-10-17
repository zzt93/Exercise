/* Mon Sep 20 17:47:01 CST 2010 */
/* strpbrk() returns a pointer */
#include <stdio.h>
#define MAX 20

static int any(const char *a, const char *b);

int main(void)
{
        char a[MAX],b[MAX];
        int ch, pos = 0;
        scanf("%s %s", a, b);
        ch = any(a,b);
        while (ch != -1) {
                pos = pos + ch + 1;
                printf("%d ", pos);
                ch = any(a + pos, b);
        }
        return(0);
}

static int any(const char *a, const char *b)
{
        int i,j;
        for (i = 0; a[i] != '\0'; i++) 
                for(j = 0; b[j] != '\0'; j++)
                        if (b[j] == a[i])
                                return i;
        return -1;
}
