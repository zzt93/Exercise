#include "skyline.h"


struct skyline_node *Divide_and_Conquer(struct skyline_node *);
void Draw_Buildings(struct skyline_node *, int);

void Refresh(GLubyte a, GLint si, GLint j)
{
        int i;
        struct skyline_node *skyline, *p;
		if (a == 'q')
                exit(0);
        skyline = malloc(sizeof(struct skyline_node));
        p = skyline;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        printf("\n\n\n****************INPUT***************\n");
        for (i = 0; i < N; i++) { /* 输入: N行, 每行1个triple (Li, Hi, Ri) */
                p->next = malloc(sizeof(struct skyline_node));
                p = p->next;
                p->h = RANDOM(20, H);
                do {
                        p->x = RANDOM(10, X);
                        p->y = RANDOM(10, Y);
                } while (p->y - p->x < 30);
                printf("(%d %d %d), ", p->x, p->h, p->y);
                p->next = NULL;
        }
        Draw_Buildings(skyline->next, 0);
        p = Divide_and_Conquer(skyline->next); /* 合并triples */
        Draw_Buildings(p, 1);
        glFlush();
        printf("\n****************OUTPUT***************\n(");
        while (p->next) {
                printf("%d, %d, ", p->x, p->h);
                p = p->next;
        }
        printf("%d, %d, %d)\n", p->x, p->h, p->y);
}

void Draw_Buildings(struct skyline_node *p, int flag)
{
        struct skyline_node *q;
        if (flag == 0) {
                glBegin(GL_LINE_STRIP);
                {
                        while (p) {
                                glVertex2i(p->x, 0);
                                glVertex2i(p->x, p->h);
                                glVertex2i(p->x, p->h);
                                glVertex2i(p->y, p->h);
                                glVertex2i(p->y, p->h);
                                glVertex2i(p->y, 0);
                                p = p->next;
                        }
                }
                glEnd();
        } else {
				q = NULL;
                glBegin(GL_LINE_STRIP);
                {
                        glVertex2i(p->x+500, 0);
                        while(p) {
                                if (q && p->x != q->y) {
                                        glVertex2i(q->y+500, 0);
                                        glVertex2i(p->x+500, 0);
                                }
                                glVertex2i(p->x+500, p->h);
                                glVertex2i(p->y+500, p->h);
                                q = p;
                                p = p->next;
                        }
                        glVertex2i(q->y+500, 0);

                }
                glEnd();
        }
}
