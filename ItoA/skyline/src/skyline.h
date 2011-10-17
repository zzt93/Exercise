#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#define N 7
#define X 450
#define H 450
#define Y 450
#define RANDOM(a, b)                            \
        (a + rand() % (b - a + 1))
#define TEST_A                                                          \
        (x1 == x0 && h1 <= h0 && y1 <= y0) ||(x1 > x0 && h1 <= h0 && x1 < y0 && y1 <= y0)

#define TEST_B                                                          \
        ( (x1 == x0) && (h1 > h0 || (h1 == h0 && y1 > y0)) )||          \
        ( (x1 > x0 && h1 == h0) && (x1 == y0 || (x1 < y0 && y1 > y0)) )

#define TEST_C                                  \
        x1 > x0 && h1 > h0 && x1 < y0

#define TEST_D                                  \
        x1 == x0 && h1 > h0

#define TEST_E                                                          \
        x1 > x0 && ( h1 > h0 || (h1 == h0 && x1 > y0) || (h1 < h0 && x1 >= y0) )

#define TEST_F                                                        \
        h1 > h0 && y1 < y0 && ( x1 == x0 || (x1 > x0 && x1 < y0) )

#define TEST_G                                                          \
        (h1 < h0 && y1 > y0) && ( (x1 == x0) || (x1 > x0 && x1 < y0) )

struct skyline_node
{
        int x;
        int h;
        int y;
        struct skyline_node *next;
};
