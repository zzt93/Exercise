//Tue Sep 21 20:52:59 CST 2010

#include <stdio.h>
#include <limits.h>
#define MAX 30

static void reverse(char s[]);
static void itoa2(int x, char s[], int n);

int main(void)
{
        char s[MAX];
        int x, n;
        scanf("%d %d", &x, &n);
        itoa2(x, s, n);
        printf("%s", s);
        return(0);
}

static void itoa2(int x, char s[], int n)
{
        int sign, i = 0;
        if ((sign = n) < 0) {
                if (n == INT_MIN)
                        n++;
                n = -n;
        }
        do {
                s[i++] = x % 10 + '0';
        } while ((x /= 10) > 0);
        if (sign < 0) {
                if (sign == INT_MIN)
                        s[0]++;
                s[i++] = '-';
        }
        s[i] = '\0';
        reverse(s);
        i--;
        for (int j = i; j >= 0; j--)
                s[j + n - 1 - i] = s[j];
        for (int j = 0; j <= n - 2 - i; j++)
                s[j] = ' ';
        s[n] = '\0';
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
