//Thu Sep 30 16:06:10 CST 2010

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LEN 3000
//i do not know whether it would work.
#define NKEYS (sizeof keytab / sizeof keytab[0])
//usage of ungetc() is not clear
struct key 
{
        char *word;
        int count;
};

static int getword(char *word, int n);
static int binsearch(struct key keytab[], char *word, int n);

int main(void)
{
        struct key keytab[] = {
                "auto", 0,
                "break", 0,
                "case", 0,
                "char", 0,
                "const", 0,
                "continue", 0,
                "default", 0,
                "unsigned", 0,
                "void", 0,
                "while", 0
        };
        char word[LEN];
        int c;
        while (getword(word, LEN) != EOF)
                if (isalpha(word[0]))
                        if ((c = binsearch(keytab, word, NKEYS - 1)) >= 0)
                                keytab[c].count++;
        for (c = 0; c < NKEYS; c++)
                if (keytab[c].count)
                        printf("%4d\t%s\n", keytab[c].count, keytab[c].word);
        return(0);
}

static int binsearch(struct key keytab[], char *word, int high)
{
        int mid, low = 0;
        while (low <= high) {
                mid = (high + low) / 2;
                if (strcmp(keytab[mid].word, word) > 0)
                        high = mid - 1;
                else if (strcmp(keytab[mid].word, word) < 0)
                        low = mid + 1;
                else
                        return mid;
        }
        
        return -1;
}
//too many returns!!!!
//structure is really poor!!!
static int getword(char *word, int len)
{
        int pch, ch, i = 0;
        while (isspace(ch = getc(stdin)))
                ;
        if (ch == EOF)
                return ch;
        word[i++] = ch;
        switch (ch) {
        case '_':
                while(!isspace(getc(stdin)))
                        ;
                break;
        case '"':
                while((ch = getc(stdin)) != '"' && ch != EOF)
                        ;
                break;
        case '#':
                while((ch = getc(stdin)) != '\n' && ch != EOF)
                        ;
                break;
        case '/':
                if ((ch = getc(stdin)) != '*') {
                        ungetc(ch, stdin);
                        return ch;
                }
                else
                        while ((ch = getc(stdin)) != EOF) {
                                if (pch == '*' && ch == '/')
                                        return ch;
                                pch = ch;
                        }
                break;          
        }
        if (!isalpha(ch)) {
                //               ungetc(ch, stdin);
                word[1] = '\0';
                return word[0];
        }
        while (i < len - 1 && isalnum(ch = getc(stdin)))
                word[i++] = ch;
        if (ch == '_') {
                while(!isspace(getc(stdin)))
                        ;
                word[0] = '\0';
                return word[0];
        }
        word[i] = '\0';
        ungetc(ch, stdin);
        return word[0];
}
