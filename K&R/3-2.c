//Tue Sep 21 16:18:55 CST 2010
//I don't know how to input '/t' or EOF in GDB
#include <stdio.h>
#include <string.h>
#define MAX 100

static void escape(char *s, const char *t);
static void nonescape(char *s, const char *t);

int main(void)
{
        int ch, i;
        char t[MAX],s[2*MAX] = "",t1[MAX];
        for(i = 0; i < MAX - 1 && (ch = getchar()) != EOF; i++)
                t[i] = ch;
        t[i] = '\0';
        escape(s,t);
        printf("%s", s);
        strcpy(t1,"");
        i = 0;
        nonescape(t1, s);
        while (t1[i])
                putchar(t1[i++]);
        return(0);
}

static void nonescape(char *s, const char *t)
{
        int i, j;
        for (i = 0, j = 0; t[i] != '\0'; i++)
                if (t[i] == '\\')
                        switch(t[++i]) {
                        case 'n':
                                s[j++] = '\n';
                                break;
                        case 't':
                                s[j++] = '\t';
                                break;
                        default:
                                s[j++] = '\\';
                                s[j++] = t[i];
                                break;
                        }
                else
                        s[j++] = t[i];
//when manipulates strings, '\0' should not be forgetten
        s[j] = '\0';
}

                

static void escape(char *s, const char *t)
{
        int i, j;
        for (i = 0, j = 0; t[i] != '\0'; i++)
                switch(t[i]) {
                case '\n':
                        //strcat(s, "\n") will copy '\n'...
                        strcat(s, "\\n\0");
                        //although adds 2 here, it really works fine
                        j += 2;
                        break;
                case '\t':
                        strcat(s, "\\t\0");
                        j += 2;
                        break;
                default:
                        s[j++] = t[i];
                        break;
                }
}

                
                
                
        
