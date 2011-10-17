/* Mon Sep 20 15:25:39 CST 2010 */
#include <stdio.h>
#include <limits.h>
#include <float.h>
/* INT_MIN = (-INT_MAX) - 1
   movl $9999, %eax
   negl %eax
   incl %eax
   decl %eax */
int main(void)
{
        signed char sch;
        signed int sint;
        signed short sshrt;
        signed long slong;
        unsigned char uch = 0;
        unsigned int uint = 0;
        unsigned short ushrt = 0;
        unsigned long ulong = 0;
        printf("signed char ranges from %d to %d.\n", CHAR_MIN, CHAR_MAX);
        printf("signed int ranges from %d to %d.\n", INT_MIN, INT_MAX);
        printf("signed short ranges from %hd to %hd.\n", SHRT_MIN, SHRT_MAX);
        printf("signed long ranges from %ld to %ld.\n", LONG_MIN, LONG_MAX);
        printf("signed long long ranges from %lld to %lld.\n", LLONG_MIN, LLONG_MAX);

        printf("unsigned char ranges from %u to %u.\n", 0, UCHAR_MAX);
        printf("unsigned int ranges from %u to %u.\n", 0, UINT_MAX);
        printf("unsigned short ranges from %hu to %hu.\n", 0, USHRT_MAX);
        printf("unsigned long ranges from %lu to %lu.\n", 0lu, ULONG_MAX);
        printf("unsigned long long ranges from %llu to %llu.\n", 0llu, ULLONG_MAX);

        printf("unsigned char ranges from %c to %c.\n", 0, ~uch);
        printf("unsigned int ranges from %u to %u.\n", 0, ~0);
        printf("unsigned short ranges from %hu to %hu.\n", 0, ~0lu);
        printf("unsigned long ranges from %lu to %lu.\n", 0ul, ~0lu);
        return(0);
}


        
                
        
        
