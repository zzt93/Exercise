#include <stdio.h>

static void itoa(int a, char *s);

int main(void)
{
        char s[10];
        int a, b, i = 0;
        scanf("%d", &a);

//the value evaluted here is b/10
        //       while (b /= 10)
        //       i++;
        // s[i+1] = '\0';
        itoa(a, s);
        printf("%s", s);
        return(0);
}
//use internal static variable here
static void itoa(int a, char *s)
{
        static pos = 0;
        if (a < 0) {
                s[pos++] = '-';
                a = -a;
        }
        if (a / 10)
                itoa(a / 10, s);
        s[pos++] = a % 10 + '0';
        s[pos] = '\0';
}

                

//V1 not very clear and can't handle negative number correctly
/* static void itoa(int a, char *s)
{
        b = (a < 0) ? -a : a;
        if (a < 0) {
                s[0] = '-';
                itoa(-a, s + 1);
        }
        if (a / 10)
                itoa(a / 10, s - 1);
        s[0] = a % 10 + '0';
}*/
