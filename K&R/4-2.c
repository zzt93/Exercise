//Wed Sep 22 00:00:37 CST 2010
//improvement!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <stdio.h>
#include <math.h>
#define MAX 30

static double atof(char a[]);

int main(void)
{
        char a[MAX];
        scanf("%s", a);
        printf("%f", atof(a));
        return(0);
}

static double atof(char a[])
{
        char ch;
        int i, j, k, multi, sum, exp;
        for (i = 0; a[i] != '\0' && a[i] != 'e' && a[i] != 'E'; i++)
                ;
        int start1, sign1, sign2;
        if (a[0] == '-') {
                start1 = 1;
                sign1 = -1;
        } else {
                start1 = 0;
                sign1 = 1;
        }
        
        
        if (a[i] != '\0') {
                for (j = start1; a[j] != '.' && a[j] != 'e' && a[j] != 'E'; j++)
                        ;
                multi = (a[j] == '.')? i - j - 1: 0;
                for (sum = 0, k = start1; a[k] != 'e' && a[k] != 'E'; k++)
                        if (a[k] != '.')
                                sum = sum*10 + a[k] - '0';
//////////////////////////////////////////////////////////////////
                while (a[j] != 'e' && a[j] != 'E')
                        j++;
                if (a[j+1] == '-') {
                        j += 2;
                        sign2 = -1;
                } else {
                        j++;
                        sign2 = 1;
                }
                
                for (exp = 0; a[j] != '\0'; j++)
                        exp = exp*10 + a[j] - '0';
                
                return ((double)sum) / pow(10, multi - exp*sign2)*sign1;
                
        } else {//needs improvement
                for (j = start1; a[j] != '.' && a[j] != '\0'; j++)
                        ;
                multi = (a[j] == '.')? i - j - 1: 0;
                for (sum = 0, k = start1; a[k] != '\0'; k++)
                        if (a[k] != '.')
                                sum = sum*10 + a[k] - '0';
                return ((double)sum)/pow(10, multi)*sign1;
        }
}

        
