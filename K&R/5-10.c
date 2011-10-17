//Wed Sep 29 13:30:57 CST 2010
//we must use escape to input arguments like '*'
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NUM 0
#define STACKSIZE 100

static double pop(void);
static void push(double a);
static int op(char *s);
static int stack_top;
static double stack[STACKSIZE];

int main(int argc, char *argv[])
{
        double op2;
        for (int i = 1; i < argc; i++) {
                switch(op(argv[i])) {
                case NUM:
                        push(atof(argv[i]));
                        break;
                case '+':
                        push(pop() + pop());
                        break;
                case '*':
                        push(pop() * pop());
                        break;
                case '-':
                        op2 = pop();
                        push(pop() - op2);
                        break;
                case '/':
                        op2 = pop();
                        push(pop() / op2);
                        break;
                }
        }
        if (stack_top != 1)
                printf("err exp!\n");
        else
                printf("%f\n", pop());
        return(0);
}

static double pop(void)
{
        if (stack_top == 0)
                printf("err exp!\n");
        else
                return stack[--stack_top];
}

static void push(double s)
{
        if (stack_top > STACKSIZE)
                printf("too long to calc!\n");
        else
                stack[stack_top++] = s;
}

static int op(char *s)
{
        if (isdigit(*s) || (!isdigit(*s) && isdigit(*(s+1))))
                return NUM;
        else
                return *s;
}


                
