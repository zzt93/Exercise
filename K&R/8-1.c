//Sat Oct  2 19:30:42 CST 2010

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFSIZE 100

int main(int argc, char *argv[])
{
        int fd, n;
        char buf[BUFSIZE];
        
        while (--argc > 0) {
                if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                        fprintf(stderr, "can't open file: %s", *argv);
                        exit(1);
                }
                while ((n = read(fd, buf, BUFSIZE)) > 0)
                        write(1, buf, n);
                if (n < 0) {
                        fprintf(stderr, "error reading file: ", *argv);
                        exit(1);
                }
                close(fd);
        }
        return(0);
}

                
                
