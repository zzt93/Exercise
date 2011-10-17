//Tue Sep 21 12:28:32 CST 2010

//it seems b1 and b2 have the same performance.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int binsearch(int x, int v[], int n, char []);
static int b1(int x, int v[], int n);
static int b2(int x, int v[], int n);

int main(int argc, char *argv[])
{
        int *p, n, x;
        char s[3];
        if (argc == 1)
                scanf("%d %d %s", &n, &x, s);
        else {
                n = atoi(argv[1]);
                x = atoi(argv[2]);
                strcpy(s, argv[3]);
        }
        if (!(p = (int*)malloc(n * sizeof(int)))) {
                printf("mem alloc err!");
                exit(0);
        }
        for (int i = 0; i < n; i++)
                p[i] = i;
        printf("%d", binsearch(x, p, n, s));
        return(0);
}

static int binsearch(int x, int v[], int n, char s[])
{
        //the way to define a pointer to a fun
        int (*p)(int, int *, int);
        //strcmp() returns 0, when a == b
        //returns -1, when a != b.
        p = (strcmp(s, "b1"))? b2: b1;
        return (*p)(x, v, n);
}

static int b1(int x, int v[], int n)
{
        int mid, low = 0;
        int high = n-1;
        //why not (low < high)
        printf("b1");
        while (low <= high) {
                mid = (low + high) / 2;
                if (x < v[mid])
                        high = mid - 1;
                else if (x > v[mid])
                        low = mid + 1;
                else
                        return mid;
        }
        return -1;
}

static int b2(int x, int v[], int n)
{
        int mid, low = 0;
        int high = n - 1;
        printf("b2");
        while (low < high) {
                mid = (low + high) / 2;
                if (x <= v[mid])
                        high = mid;
                else
                        low = mid + 1;
        }
        return (x == v[low])?low : -1;
}
