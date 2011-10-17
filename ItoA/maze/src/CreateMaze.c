#include "maze.h"

void CreatePath(struct room []);
int CheckPath(struct room [], int);
void CreateObject(struct room []);
void PrintMaze(struct room maze[]);

void CreateMaze(struct room maze[])
{
        int i;
        do {
                for (i = 0; i < NR_ROOM; i++) {
                        maze[i].in = malloc(sizeof(struct node)); /* 初始化头节点 */
                        (maze[i].in)->next = NULL;
                        maze[i].out = malloc(sizeof(struct node));
                        (maze[i].out)->next = NULL;
                }
                CreatePath(maze); /* 建立房间之间的路径 */
        } while (!CheckPath(maze, 0)); /* 判断是否能从0号房间到达NR_ROOM-1号房间 */
        CreateObject(maze);     /* 创造怪物和药剂 */
}

void CreateObject(struct room maze[])
{
        int x, i, tmp, created[NR_ROOM];
        struct node *p, *pout;
        for (i = 0; i < NR_ROOM; i++)
                created[i] = 0;
        for (i = 1; i <= NR_MONSTER + NR_POTION; i++) {
                do {
                        tmp = RANDOM(0, NR_ROOM - 1);
                } while (created[tmp]);
                created[tmp] = 1; /* 在房间tmp创建目标 */
                p = (maze[tmp].in)->next; /* 以tmp为目标的边 */
                x = (i <= NR_MONSTER) ?
                        - RANDOM(DROP_MIN, DROP_MAX) : RANDOM(HEAL_MIN, HEAL_MAX);
                while (p) {
                        p->x = x;
                        pout = (maze[p->room].out)->next;
                        while (pout->room != tmp )
                                pout = pout->next;
                        pout->x = x;
                        p = p->next;
                }
        }
}

void CreatePath(struct room maze[])
{
        struct node *p;
        int i, j, a, b, matrix[NR_ROOM][NR_ROOM]; /* 临时记录路径创建情况 */
        for (i = 0; i < NR_ROOM; i++)
                for (j = 0; j < NR_ROOM; j++)
                        matrix[i][j] = (i == j);
        
        for (i = 1; i <= NR_PATH; i++) {
                do {
                        a = RANDOM(0, NR_ROOM - 1);
                        b = RANDOM(0, NR_ROOM - 1);
                } while (matrix[a][b]);/* 如果目前没有a到b的路径，那么建立一条 */
                matrix[a][b] = 1;
                
                p = maze[a].out;        /* 更新a的邻接表 */
                while (p->next != NULL)
                        p = p->next;
                p->next = malloc(sizeof(struct node));
                p = p->next;
                p->room = b;
				p->x = 0;
                p->next = NULL;
                
                p = maze[b].in;         /* 更新b的邻接表 */
                while (p->next != NULL)
                        p = p->next;
                p->next = malloc(sizeof(struct node));
                p = p->next;
                p->room = a;
				p->x = 0;
                p->next = NULL;
                
        }
}

int CheckPath(struct room maze[], int a)
{
        int i, tmp, stack_top, stack[NR_ROOM], visited[NR_ROOM];
        struct node *p;
        for (i = 0; i < NR_ROOM; i++)
                visited[i] = 0;
        stack_top = 0;
        PUSH(stack, a, stack_top);
        while (!EMPTY(stack, stack_top)) { /* DFS遍历图 */
                tmp = POP(stack, stack_top);
                visited[tmp] = 1;
                p = maze[tmp].out->next;
                while (p) {
                        if (!visited[p->room])
                                PUSH(stack, p->room, stack_top);
                        p = p->next;
                }
        }
        return visited[NR_ROOM - 1];
}       

void PrintMaze(struct room maze[])   /* 输出图 */
{
        struct node *p;
        int i;
        for (i = 0; i < NR_ROOM; i++) {
                p = maze[i].out->next;
                if (p)
                        printf("+------------------------------------------------+\n");

                while (p) {
                        printf("|     Room %2d   =====(%+4d)=====>   Room %2d      |\n", i, p->x, p->room);
                        p = p->next;
                }
        }
        printf("+------------------------------------------------+\n");
}

        








        
        
