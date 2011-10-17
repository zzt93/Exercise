//Wed Sep 22 11:11:31 CST 2010

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#define NUM '0'
#define MAXOP 20

static void push(double f);
static double pop(void);
static int getop(char s[]);

int main(void)
{
        int type;
        char s[MAXOP];
        double op2, last = 0;
        //the idea of getop() is good
        while ((type = getop(s)) != EOF) {
                switch (type) {
                case NUM:
                        push(atof(s));
                        break;
                case '+':
                        push(pop() + pop());
                        break;
                case '-':
                        op2 = pop();//push(pop() - pop()),....
                        push(pop() - op2);
                        break;
                case '*':
                        push(pop() * pop());
                        break;
                case '/':
                        op2 = pop();
                        push(pop() / op2);
                        break;
                case '%':
                        op2 = pop();
                        push((int)pop() % (int)op2);
                        break;
                case 's':
                        getop(s);
                        push(sin(atof(s)));
                        break;
                case 'x':
                        push(last);
                        break;
                        
                case '\n':
                        printf("%f\n", (last = pop()));
                        break;
                default:
                        printf("unknown expression!");
                        exit(0);
                }
        }
        return(0);
}

#define STACK_MAX 50
double stack[STACK_MAX];
int stack_top;

static void push(double f)
{
        stack[stack_top++] = f;
}

static double pop(void)
{
        return stack[--stack_top];
}


//V2
static int getch(void);
static void ungetch(int);

static int getop(char s[])
{
        int ch, i = 0;
        while (isspace(ch = getch()) && ch != '\n')
                ;
        if (!isdigit(ch)) {
                if (ch == '-' && stack_top !=2) {
                        ch = getch();
                        s[i++] = '-';
                }
                else
                        return ch;
        }
        do {
                s[i++] = ch;
        } while (isdigit(ch = getch()) || ch == '.');
        s[i] = '\0';
        ungetch(ch);
        return NUM;
}

#define BUFSIZE 1
char buf[BUFSIZE];
int bufp = 0;

static int getch(void)
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

static void ungetch(int ch)
{
        if (bufp == BUFSIZE)
                printf("ungetch: too many chars\n");
        else
                buf[bufp++] = ch;
}







//V1 not very good
/*static int getop(char s[])
  {
  int ch, sign, i = 0;
  while (isspace(ch = getchar()) && ch != '\n')
  ;
  if (!isdigit(ch)) {
  if (ch == '-' && stack_top != 2) {
  ch = getchar();
  s[i++] = '-';
  }
  else
  return ch;
  }
  do {
  s[i++] = ch;
  } while (!isspace(ch = getchar()));
  s[i] = '\0';
  return NUM;
  }*/
