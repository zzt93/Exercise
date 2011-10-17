/* Mon Sep 20 15:26:17 CST 2010 */
#include <stdio.h>

int main(void)
{
        char s[11],t[11],lim = 10;
        //int c,i;
        
        /* unsigned char can't recognize EOF.
         on some machine, char is not implemented with
        int or signed char, so it's better to use int
        instead of char.*/

        unsigned char c;
        int i;

        for(;c != EOF;){
                c = getchar();
                putchar(c);
        }
        /*      
        for (i = 0; i <= lim-1 && (c = getchar()) != '\n' && c != EOF; i++)
                s[i] = c;
        s[i] = '\0';

        
        for (i = 0; i <= lim-1; i++) {
 
                if ((c = getchar()) == '\n')
                        break;
                if (c == EOF)
                        break;
                t[i] = c;
        }
        t[i] = '\0';
        
        printf("%s,%d\n", s,EOF);
        printf("%s\n", t);*/
        return(0);
        
}

        
