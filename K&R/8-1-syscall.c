//Fri Oct  1 20:17:40 CST 2010
//isprint() isgraph()
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static int oct, width = 40;

int main(int argc, char *argv[])
{
        int c, w = 0;
        char word[10];
        if (argc == 1) {
                printf("usage: read -o -w \n");
                exit(0);
        }
        while (--argc > 0 && *(++argv)[0] == '-')
                while ((c = *++argv[0]) != '\0')
                        switch (c) {
                        case 'o':
                                oct = 1;
                                break;
                        case 'w':
                                if ((width = atoi(*(argv+1))) == 0) {
                                        printf("illegal width!\n");
                                        exit(0);
                                }
                                break;
                        default :
                                printf("unknown option: %c\n", c);
                                exit(0);
                                break;
                        }
        while (read(0, &c, 1) > 0) {
                if (c == '\n') {
                        w = 0;
                        write(1, &c, 1);
                        continue;
                }
                if (w >= width) {
                        w = 0;
                        write(1, "\n", 1);
                }
                if (isprint(c)) {
                        write(1, &c, 1);
                        w++;
                } else {
                        //skill!!!!!!!!!!!!
                        sprintf(word, (oct) ? " /%o" : " 0x%x", c);
                        if ((w += strlen(word)) > width) {
                                write(1, "\n", 1);
                                w = 0;
                        }
                        printf("%s", word);

                }
                
        }
        putc('\n', stdout);
        return(0);
}
