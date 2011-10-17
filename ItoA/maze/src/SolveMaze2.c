#include "maze.h"

int testc2(struct room maze[], int); 
int CheckPath(struct room [], int);
void update(struct room [], int [], int, int, int);

int SolveMaze2(struct room maze[])
{
        int a, b, x = 1;
        while (1) {             /* 寻找初始生命的上界 */
                if (!testc2(maze, x))
                        x *= 2;
                else
                        break;
        }
        a = x/2;
        b = x;
        while (a <= b) {        /* 二分查找最低初始生命 */
                x = (a+b)/2;
                if (!testc2(maze, x))
                        a = x + 1;
                else
                        b = x - 1;
        }
        return (a == 0) ? 1 : a;
}

int testc2(struct room maze[], int c) /* 判断以初始生命c能否从房间0到房间NR_ROOM-1 */
{
        int i, j, sum, life[NR_ROOM];
        struct node *p;
        for (i = 0; i < NR_ROOM; i++)
                life[i] = -65536;
        life[0] = c;            /* 初始生命 */
        for (i = 0; i < NR_ROOM; i++) {
                for (j = 0; j < NR_ROOM; j++) { /* 对每条边进行处理 */
                        p = (maze[j].out)->next;
                        while (p) {
                                update(maze, life, j, p->room, p->x);
                                p = p->next;
                        }
                }
        }
        if (life[NR_ROOM-1] > 0) /* 经过NR_ROOM次迭代能否到达终点 */
                return 1;
        else {       
                for (i = 0, sum = 0; i < NR_ROOM; i++) {
                        p = (maze[i].out)->next;
                        while (p) {
                                if (life[i] + p->x > life[p->room] && life[i]+p->x > 0) /* 寻找正权值环内的节点 */
                                        sum += CheckPath(maze, i); /* 对每一个可能的环判断是否能从该环到达终点 */
                                p = p->next;
                        }
                }
                return sum;    
        }
        
}

void update(struct room maze[], int life[], int u, int v, int weight)
{
        int tmp = life[u] + weight;
        if (tmp > 0 && tmp > life[v])
                life[v] = tmp;
}

        

