/* Mon Sep 20 15:26:48 CST 2010
 */

#include <stdio.h>
#include <string.h>
#define MAX 20
static void sq(char *s, const char *c);

int main(void)
{
        char s[MAX], c[MAX];
        /* i do not know why scanf("%s, %s, s, c) doesn't work */
        scanf("%s %s", s, c);
        sq(s, c);
        printf("%s", s);
        return(0);
}
/* good method */
void sq(char *s, const char *c)
{
        int i,j,k;
        for (i = 0; c[i]; i++) {
                for (j = 0, k = 0; s[j]; j++)
                        if (s[j] != c[i])
                                s[k++] = s[j];
                s[k] = '\0';
        }
}

                        
                
        
