//Tue Sep 21 19:20:40 CST 2010

#include <stdio.h>
#include <limits.h>
#define MAX 30

static void atob(int x, char a[], int b);
static void reverse(char s[]);

int main(void)
{
        char a[MAX];
        int x, b;
        scanf("%d %d", &x, &b);
        atob(x, a, b);
        reverse(a);
        printf("%s", a);
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
static void atob(int x, char a[], int b)
{
        int i = 0, sign;
        if ((sign = x) < 0) {
                if (x == INT_MIN)
                        x++;
                x = -x;
        }
        do {
                //x % b + (x%b >9)? 'A'-10: '0' does not work
                //'A'-10 is good
                a[i++] = x % b + ((x % b > 9)? 'A'-10: '0');
        } while ((x /= b) > 0);
        if (sign < 0) {
                if (sign == INT_MIN)
                        a[0]++;
                a[i++] = '-';
        }
        a[i] = '\0';
}
