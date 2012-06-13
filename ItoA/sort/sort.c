#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"

int heapsize;
static void Qsort(char *array, int p, int r);
static void Hsort(char *array, int size);

int main(int argc, char **argv)
{
        if (strcmp(argv[1], "-gen") == 0)
                genfile(argv[3], atoi(argv[2]));
        else if (strcmp(argv[1], "-sort") == 0) {
                char *array;
                int size = readfile(argv[3], &array);
                if (strcmp(argv[2], "q") == 0)
                    Qsort(array, 0, size - 1);
                else if (strcmp(argv[2], "h") == 0)
                             Hsort(array, size - 1);
                else goto err;
                writefile(array, size);
        } else
        err:
                printf("unknown command %s\n"
                       "usage: %s -gen size file\n"
                       "       %s -sort {q, h} file\n",
                       argv[2], argv[0], argv[0]);
        return 0;
}

                /* quick sort routine */

static void Qsort(char *array, int p, int r)
{
        if (p >= r)
                return;
        int i, j;
        for (i = p - 1, j = p; j <= r; j++)
                if (array[j] <= array[r])
                        exchange(&array[j], &array[++i]);
        Qsort(array, p, i - 1);
        Qsort(array, i + 1, r);
}

                /* heap sort routine */

static inline void heapify(char *array, int n);
static void Hsort(char *array, int size)
{
        heapsize = size;
        for (int i = P(size); i >= 0; i--)
                heapify(array, i);
        for (int i = size; i >= 1; i--) {
                exchange(&array[0], &array[heapsize--]);
                heapify(array, 0);
        }
}

static inline void heapify(char *array, int n)
{
        int l, r, largest = n;
        do {
                l = L(n);
                r = R(n);
                if (l <= heapsize && array[l] > array[n])
                        largest = l;
                if (r <= heapsize && array[r] > array[largest])
                        largest = r;
                if (largest == n) break;
                exchange(&array[n], &array[largest]);
                n = largest;
        } while (1);
}
