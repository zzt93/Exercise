#include <stdio.h>

int globalvar1;
int globalvar2 = 3;

void localfoo(void)
{
        int functionvar;
        printf("variable functionvar \t location: 0x%x\n", &functionvar);
}

int main(void)
{
        void *localvar1 = (void *) malloc(2048);
        printf("variable globalvar1 \t location: 0x%x\n", &globalvar1);
        printf("variable globalvar2 \t location: 0x%x\n", &globalvar2);
        printf("variable localvar1 \t location: 0x%x\n", localvar1);
        
        mylibfoo();
        localfoo();
        
        while(1)
                ;
        return(0);
}
