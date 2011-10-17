#include "maze.h"

void DFS(struct room [], int, int, int);
int CheckPath(struct room[], int);
int min;

int SolveMaze3(struct room *maze)
{
        min = -65535;
        DFS(maze, 0, 0, 65535);
        return (min > 0) ? 1 : -min + 1;
}

void DFS(struct room *maze, int p, int life, int min_t)
{
        static int visiting[NR_ROOM], l[NR_ROOM];
        struct node *q = maze[p].out->next;
        if (visiting[p]) {        /* 判断是否存在环 */
                if (l[p] < life && CheckPath(maze, p)) { /* 判断是否正权值环 */
                        min = (min_t > min) ? min_t : min;
                        return;
                } else
                        return;
        }
        if (p == NR_ROOM - 1) { /* 到达终点 */
                if (min_t > min)
                        min = min_t;
                return;
        }
        visiting[p] = 1;
        l[p] = life;
        while(q) {
                DFS(maze, q->room, life + q->x,
                    (life + q->x < min_t) ? life + q->x : min_t);
                q = q->next;
        }
        visiting[p] = 0;
}

        
                
