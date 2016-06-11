#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    srand48(time(NULL));
    double i = drand48() * 1000;
    printf("%g\n", i);

}

