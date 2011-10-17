//Wed Sep 22 13:06:27 CST 2010
//I don't know whether 'Char p[100]' will work in fun when return it

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STACK_SIZE 100


typedef char *string;
string stack[STACK_SIZE];
int stack_top = -1;

static void push(const string s);
//static string pop(void) will cause the return of local value
static void pop(string s);
//again
static string gettop(void);
//dup does not work
static void duplicate(void);
static void swaptop(void);
static void clearstack(void);
static void printstack(void);

int main(void)
{
        char cmd[100],tmp[100];
        while (1) {
                gets(cmd);
                if (strstr(cmd, "psh"))
                        push("ppuusshh");
                else if (strstr(cmd, "pop")) {
                        pop(tmp);
                        printf("%s\n", tmp);
                }
                else if (strstr(cmd, "gt"))
                        printf("%s\n", gettop());
                else if (strstr(cmd, "dup"))
                        duplicate();
                else if (strstr(cmd, "swp"))
                        swaptop();
                else if (strstr(cmd, "cl"))
                        clearstack();
                else
                        printf("psh, pop, gt, dup, swp, cl\n");
                printstack();
                        }
}



static void push(const string s)
{
        if (stack_top == STACK_SIZE)
                printf("stack full!");
        else {
                //pay attention
                stack[++stack_top] = (string) malloc(20*sizeof(char));
                strcpy(stack[stack_top], s);
        }
        
}

static void pop(string s)
{
        if (stack_top == -1)
                printf("stack empty!");
        else
                strcpy(s, stack[stack_top--]);
}

static string gettop(void)
{
        char p[100];
        if (stack_top == -1)
                printf("stack empty!");
        else {
                strcpy(p, stack[stack_top]);
                return p;
        }
        return NULL;
}

static void duplicate(void)
{
        if (stack_top == STACK_SIZE)
                printf("stack full!");
        else 
                push(gettop());
}

static void swaptop(void)
{
        string p;
        p = stack[stack_top];
        stack[stack_top] = stack[stack_top - 1];
        stack[stack_top - 1] = p;
}

static void clearstack(void)
{
        stack_top = -1;
}

static void printstack(void)
{
        for (int i = 0; i <= stack_top; i++)
                printf("%s\n", stack[i]);
}
