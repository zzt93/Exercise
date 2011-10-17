//Tue Sep 21 12:11:50 CST 2010

#include <stdio.h>

static int tolower(int ch);

int main(void)
{
        int ch;
//I don't know why in gdb the output isn't right
        while ((ch = getchar()) != EOF) 
                putchar(tolower(ch));
        return(0);
}

static int tolower(int ch)
{
        return (ch >= 'A' && ch <= 'Z')? ch + 'a' - 'A': ch;
}

                
        
