#include "maze.h"

int testc(struct room maze[], int, int); 
int CheckPath(struct room [], int);

int SolveMaze1(struct room maze[])
{
        int a, b, x = 1;
        while (1) {             /* 寻找初始生命的上界 */
                if (!testc(maze, 0, x))
                        x *= 2;
                else
                        break;
        }
        a = x/2;
        b = x;
        while (a <= b) {        /* 二分查找最低初始生命 */
                x = (a+b)/2;
                if (!testc(maze, 0, x))
                        a = x + 1;
                else
                        b = x - 1;
        }
        return (a == 0) ? 1 : a;
}

int testc(struct room maze[], int p, int c) /* 判断以初始生命c
                                               从第p个房间出发能否到达终点(NR_ROOM-1) */
{
        int tmp, sum = 0;
        static int visited[NR_ROOM]; /* visited: -1 正在访问子节点, 0 没有访问过, 1 已经访问过 */
        static int life[NR_ROOM];    /* 记录到达该房间后的血量, 用于检测正权值环 */
        struct node *q;
        if (p == NR_ROOM - 1) {                 /* 如果到达终点则返回 */
                visited[p] = 1;
                return 1;
        }
        visited[p] = -1;
        q = (maze[p].out)->next; /* 越过头节点 */
        life[p] = c;
        while (q) {
                if (c + q->x > 0) {/* 分治 */
                        if (visited[q->room] == -1) /* 遇到正在访问的节点说明存在环 */
                                if (life[q->room] < c + q->x) /* 正权值的环,判断分叉口到终点是否连通 */
                                        tmp = CheckPath(maze, q->room);
                                else 
                                        tmp = 0; /* 负权值的环无视 */
                        else {
                                life[q->room] = c + q->x;
                                tmp = testc(maze, q->room, c + q->x);
                        }
                        sum += tmp;
                }
                q = q->next;
        }
        visited[p] = 1;
        return sum;
}


