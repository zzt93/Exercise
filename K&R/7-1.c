//Fri Oct  1 20:01:52 CST 2010

#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
        int c;
        while ((c = getc(stdin)) != EOF)
                putc((strcmp(argv[0], ".//upper")) ? tolower(c) : toupper(c), stdout);
        return(0);
}
