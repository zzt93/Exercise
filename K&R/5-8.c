//Mon Sep 27 23:36:14 CST 2010

#include <stdio.h>

static int day_year(int year, int month, int day);
static int month_day(int year, int day, int *month, int *mday);
int d[2][13] = {\
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},   \
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}     \
};
int main(void)
{

        int year, month, day, ch, mday;
        while ((ch = getc(stdin)) != EOF) {
                if (ch == 'd') {
                        scanf("%d %d %d", &year, &month, &day);
                        printf("%d\n", day_year(year, month, day));
                }
                else if (ch == 'm') {
                        scanf("%d %d", &year, &day);
                        month_day(year, day, &month, &mday);
                        printf("%d %d\n", month, mday);
                }
                else
                        printf("err\n");
        }
        return(0);
}

static int day_year(int year, int month, int day)
{
        int leap;
        //precedence....
        leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
        for (int i = 1; i < month; i++)
                day += d[leap][i];
        return day;
}

static int month_day(int year, int day, int *month, int *mday)
{
        int leap;
        *month = 1;
        *mday = day;
        leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
        while (*mday > d[leap][*month]) {
                *mday -= d[leap][*month];
                (*month)++;
        }
        return(0);
}

        
        
        
        
                
        
        
                
                
