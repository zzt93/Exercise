//Sat Oct  2 13:35:05 CST 2010

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100

int main(int argc, char *argv[])
{
        FILE *f1, *f2;
        char l1[MAXLINE], l2[MAXLINE];
        int i = 1;
        if (argc != 3) {
                fprintf(stderr, "%s: err input!", argv[0]);
                exit(1);
        }
        if (!((f1 = fopen(argv[1], "r")) && (f2 = fopen(argv[2], "r"))))
                fprintf(stderr, "file err!");
        
        while (fgets(l1, MAXLINE, f1) && fgets(l2, MAXLINE, f2) && !strcmp(l1, l2))
                i++;
        //have to ..
        if (!strcmp(l1, l2))
                fprintf(stdout, "%s, %s are the same\n", argv[1], argv[2]);
        else {
                fprintf(stdout, "%s, %s differs in line %d\n", argv[1], argv[2], i);
                fprintf(stdout, "%s: %s\n", argv[1], l1);
                fprintf(stdout, "%s: %s\n", argv[2], l2);
        }
//easy to forget
        fclose(f1);
        fclose(f2);
        return(0);
}
