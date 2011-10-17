//Wed Sep 29 15:00:42 CST 2010

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100

static char *getline(int max);

int main(int argc, char *argv[])
{
        int n = 10, j = 0, lines = 0;
        char **p_line;
        if (argc == 1)
                ;
        else if (argc != 2 || argv[1][0] != '-' || (n = -atoi(argv[1])) < 0) {
                        printf("usage: %s -n\n", argv[0]);
                        exit(0);
                }
        p_line = (char**) malloc(sizeof(char*) * (n + 1));
        while ((p_line[n] = getline(MAXLEN)) != NULL)           
                for (int i = 0; i < n; i++)
                        p_line[i] = p_line[i+1];
        for (int i = 0; i < n; i++)
                if (p_line[i] != NULL)
                        printf("%s\n", p_line[i]);
        return(0);
}

static char *getline(int max)
{
        char t[max], *s;
        int ch, i;
        for (i = 0; i < max - 1 && (ch = getc(stdin)) != '\n' && ch != EOF; i++)
                t[i] = ch;
        if (ch == EOF && i == 0)
                return NULL;
        t[i] = '\0';
        s = malloc(sizeof(char) * strlen(t) + 1);
        strcpy(s, t);
        return s;
}

        
        
        
