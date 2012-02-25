/* Sat Jan  7 20:15:25 CST 2012 */

#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define SMPL_INTRVL 1000000     /* the task manager refreshs */
#define SMPL_N 20               /* the number of samples of sine*/
#define PI 3.14159265358979323

/* better on uni-processor */
#define CPU_AFFINITY(cpu)                                               \
        {                                                               \
                cpu_set_t mask;                                         \
                CPU_ZERO(&mask);                                        \
                CPU_SET((cpu), &mask);                                  \
                sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask);  \
        }

/* transform struct timeval to double, so that we can compare them */
#define TMVAL2DOUBLE(tmval)                                 \
        (tmval).tv_sec + (double) (tmval).tv_usec / 1000000

/* keep the cpu busy for usec microseconds */
#define CPU_BSY(usec)                                       \
        {                                                   \
                struct timeval start_tm, now;               \
                gettimeofday(&start_tm, NULL);              \
                double until = TMVAL2DOUBLE(start_tm) +     \
                        (double) (usec) / 1000000;          \
                do {                                        \
                        gettimeofday(&now, NULL);           \
                } while (TMVAL2DOUBLE(now) < until);        \
        }

/* calculate the sample array */
#define GET_BSY_ARRAY(arr)                                            \
        {                                                             \
                for (int i = 0; i < SMPL_N; i++)                      \
                        (arr)[i] = (sin(2 * PI * i / SMPL_N) + 1)/2 ; \
        }                                                             \

/* this is where we have the work done */
#define DRAW(percent)                                  \
        {                                              \
                CPU_BSY(SMPL_INTRVL * (percent));      \
                usleep(SMPL_INTRVL * (1 - (percent))); \
        }                                              \
                
int main(void)
{
        double bsyarr[SMPL_N];
        
        CPU_AFFINITY(3);
        GET_BSY_ARRAY(bsyarr);
        
        for (unsigned i = 0; true; i++)
                DRAW(bsyarr[i % SMPL_N]);

        return(0);
}

                
        
        
        
