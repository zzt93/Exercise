#include "skyline.h"

struct skyline_node *Combine(struct skyline_node *, struct skyline_node *);
struct skyline_node * add(struct skyline_node *, struct skyline_node *);

struct skyline_node *Divide_and_Conquer(struct skyline_node *skyline)
{
        struct skyline_node *first = skyline;
        struct skyline_node *second = skyline;
        if (first->next == NULL)
                return first;
        while (second->next != NULL && second->next->next != NULL) { 
                first = first->next;
                second = second->next->next;
        } /* first指向中点 */
        second = first->next;
        first->next = NULL;
        first = skyline;        /* 分割成两段链表 */
        return Combine(Divide_and_Conquer(first), Divide_and_Conquer(second));
        /* Divide_and_Conquer返回合并之后的链表首元素地址 */
}

struct skyline_node *Combine(struct skyline_node *first, struct skyline_node *second)
/* Combine合并以first和second为首元素地址的链表 */
{
        struct skyline_node *head = malloc(sizeof(struct skyline_node));
        struct skyline_node *current = head;
        current->x = -65535;
        current->h = -65535;
        current->y = -65535;
        while (first && second) { /* 不断加入较小的triple */
                if (first->x <= second->x) {
                        current = add(current, first); /* 针对各种不同的前后元素情况进行处理 */
                        first = first->next;
                } else {
                        current = add(current, second);
                        second = second->next;
                }                
        }
        while (first) {
                current = add(current, first);
                first = first->next;
        }
        while (second) {
                current = add(current, second);
                second = second->next;
        }
        return head->next;
}

struct skyline_node *add(struct skyline_node *current, struct skyline_node *node)
{
        int x0, h0, y0, x1, h1, y1;
        x0 = current->x;
        h0 = current->h;
        y0 = current->y;
        x1 = node->x;
        h1 = node->h;
        y1 = node->y;
        if (TEST_A)
                return current;
        if (TEST_B)
                current->y = y1;
        if (TEST_C)
                current->y = x1;
        if (TEST_D)
                current->h = h1;
        if (TEST_E) {
                current->next = malloc(sizeof(struct skyline_node));
                current = current->next;
                current->x = x1;
                current->y = y1;
                current->h = h1;
        }
        if (TEST_F) {
                current->next = malloc(sizeof(struct skyline_node));
                current = current->next;
                current->x = y1;
                current->h = h0;
                current->y = y0;
        }
        if (TEST_G) {
                current->next = malloc(sizeof(struct skyline_node));
                current = current->next;
                current->x = y0;
                current->h = h1;
                current->y = y1;
        }
        current->next = NULL;
        return current;
}

