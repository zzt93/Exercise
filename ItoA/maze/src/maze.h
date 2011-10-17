#include <stdlib.h>
#include <stdio.h>

#define NR_ROOM 15             /* 房间数目 */
#define NR_PATH 15             /* 路径数目 */
#define NR_MONSTER 10           /* 怪兽数目 */
#define NR_POTION 5            /* 药剂数目 */
#define DROP_MAX 100            /* 怪兽最大伤害 */
#define DROP_MIN 10             /* 怪兽最低伤害 */
#define HEAL_MAX 10            /* 药剂最大治疗 */
#define HEAL_MIN 5              /* 药剂最小治疗 */

#define RANDOM(a, b)                            \
        (a + rand() % (b - a + 1))
#define PUSH(stack, element, top)               \
        stack[top++] = element
#define POP(stack, top)                         \
        stack[--top]
#define EMPTY(stack, top)                       \
        top == 0

struct node
{
        int room;               /* 房间号 */
        int x;                  /* x>0表示药剂，x<0表示怪兽 */
        struct node *next;
};

struct room                     /* 十字链表 */
{
        struct node *in;        /* 能到达该房间的node链表 */
        struct node *out;       /* 从该房间出发能到达的node链表 */
};                              /* 默认0号房间为入口，
                                   N-1号为出口房间*/

