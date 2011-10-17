//Tue Sep 21 18:32:48 CST 2010
//maybe there are better approaches
//-2147483648 with hex not right!!!
#include <stdio.h>
#include <limits.h>
static void itoa(int n, char s[]);
static void reverse(char s[]);

int main(void)
{
        int n;
        char s[20];
        scanf("%d", &n);
        itoa(n, s);
        reverse(s);
        printf("%s", s);
        return(0);
}
static void reverse(char s[])
{
        char ch;
        int j = 0,k,i = 0;
        //pay attentation here
        while (s[j++])
               ;
        j -= 2;
        for (i = 0, k = j; i <= k; i++, k--) {
                ch = s[i];
                s[i] = s[k];
                s[k] = ch;
        }
}


static void itoa(int n, char s[])
{
        int i, sign;
        if ((sign = n) < 0) {
                if (sign == INT_MIN)
                        n++;
                n = -n;
        }
        i = 0;
//this do-while is perfact
        do {
                s[i++] = n % 10 + '0';
        } while ((n /= 10) > 0);
        if (sign < 0) {
                if (sign == INT_MIN)
                        s[0]++;
                s[i++] = '-';
        }
//again... ...
        s[i] = '\0';
}
