//Tue Sep 21 18:02:57 CST 2010

#include <stdio.h>
#define MAX 100

static void expand(const char *s1, char *s2);

int main(void)
{
        char s1[MAX] = "",s2[MAX] = "";
        scanf("%s", s1);
        expand(s1, s2);
        printf("%s", s2);
        return(0);
}

static void expand(const char *s1, char *s2)
{
        int i, j, k;
        for (i = 0, k = 0; s1[i] != '\0'; i++)
                //this condition is really perfact!
                if (s1[i] == '-' && i-1 >= 0 && s1[i+1] != '\0')                                 
                        for (j = s1[i-1] + 1; j <= s1[i+1] - 1; j++)
                                s2[k++] = (char) j;
                else
                        s2[k++] = s1[i];
        //never forget
        s2[k] = '\0';
}

        
