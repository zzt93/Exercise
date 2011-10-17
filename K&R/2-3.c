/* Mon Sep 20 15:23:05 CST 2010

/* 'C-u M-! date': insert date
 C-c: comment select code */
#include <stdio.h>
#include <ctype.h>              /* isdigit(), isxdigit() */
#include <stdlib.h>             /* exit() */
#define MAX 20

int main(void)
{
        char hex[MAX];
        int ch,i;
        unsigned long long sum = 0;
        printf("Hex: (optional 0x,0X): ");
        for (i = 0; i < MAX && (ch = getchar()) != '\n' && ch != EOF; i++)
                hex[i] = tolower(ch);
        /* when for exits, i is always the new val */
        hex[i] = 'o';
        i = (hex[1] == 'x')? 2: 0;
        while (hex[i] != 'o') 
                if (isdigit(hex[i]))
                        sum = sum * 16 + (hex[i++] - '0');
                else if (isxdigit(hex[i]))
                        sum = sum * 16 + (hex[i++] - 'a' + 10);
                else {
                        printf("wrong hex input!");
                        exit(0);
                }
        printf("the dec is %llu", sum);
        return(0);
}

                
                
                

        
