#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_THREADS 3  // max # of threads to create

#define MIN_BLOCK_SIZE 100 // min size of an array block

#define ARR_LEN 500 

typedef struct {
    float *start;
    int len;
    int block_size;
    double sum;
} Sum_arg;

int parallel_sum(void *arg);

bool sum(float arr[], int len, double* sumPtr)
{
    int block_size = len / MAX_THREADS;
    if (block_size < MIN_BLOCK_SIZE) block_size = len;

    Sum_arg args = { arr, len, block_size, 0.0 };
    if (parallel_sum(&args))
    	{ *sumPtr = args.sum; return true; }
    else
    	return false;
}


int parallel_sum(void *arg)
{
    Sum_arg *argp = (Sum_arg*)arg; // pointer to the args
    int tid = pthread_self();
    printf("pthread_self = %x\n", tid);
    printf("Arg->start %d argp->float = %g arg->mid = %d\n", 
        argp->start, *argp->start, argp->len);

    if (argp->len <= argp->block_size) // if length <= block_size
    {                                   // add up the elements
        for (int i = 0; i < argp->len; ++i)
            argp->sum += argp->start[i];
        return 1;
    }
    else
    {
        int mid = argp->len / 2;
        Sum_arg arg2 = { argp->start + mid, argp->len - mid,
                        argp->block_size, 0};  // 2nd half
        argp->len = mid;                         // Len of first half

        pthread_t th; // process 1st half in a new thread
        int res = 0;
        int tid = pthread_create(&th, NULL, &parallel_sum, arg);
        if (tid != 0)
            return 0;

        if (!parallel_sum(&arg2)) // process 2nd half by recursion
        {
            pthread_detach(th); return 0; // Recursive call failed
        }
        pthread_join(th, (void*)&res);
        if (!res)
            return 0;

        argp->sum += arg2.sum;
        return 1;
    }
}

int main()
{
    srand(time(NULL));
    float farr[ARR_LEN];
    int i = 0;
    for ( ; i < ARR_LEN; i++) {
        float res = (float)rand()  / 1000000.0;
        farr[i]  = res;
    }
    double * sum_ptr = malloc(sizeof(double));
    double res = sum(farr, ARR_LEN, sum_ptr);

    i = 0;
    printf("\n\n");

    printf("res = %.02f\n", *sum_ptr);
	return 0;
}

