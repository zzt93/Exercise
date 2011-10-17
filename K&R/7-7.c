//Sat Oct  2 15:21:42 CST 2010

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 100

static int expect, number;
static void findinfile(FILE *f, char *key);

int main(int argc, char *argv[])
{
        int c;
        //a pointer
        FILE *f;
        char key[MAXLEN];
        strcpy(key, argv[argc-1]);
        while (--argc > 0 && (*++argv)[0] == '-')
                //argv[0] is a pointer
                while (c = *++argv[0])
                        switch (c) {
                        case 'x':
                                expect = 1;
                                break;
                        case 'n':
                                number = 1;
                                break;
                        default:
                                fprintf(stderr, "unknown option %c", c);
                                exit(1);
                                break;
                        }
        while (argc-- > 1) {
                if (!(f = fopen(*argv++, "r"))) {
                        fprintf(stderr, "error file!\n");
                        exit(1);
                }
                printf("%s: ", *(argv - 1));
                findinfile(f, key);
                fclose(f);
        }
        return(0);
}

static void findinfile(FILE *f, char *key)
{
        char word[MAXLEN];
        int lineno = 0;
        int found = 0;
        while (fgets(word, MAXLEN, f)) {
                lineno++;
                if (strstr(word, key)) {
                        found++;
                        if (number)
                                printf("\nline %d", lineno);
                        
                }
        }
        printf("\n%d found\n\n", found);
}

                        
        
