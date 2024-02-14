#include<stdlib.h>
#include<stdio.h>
#include "xmalloc.h"

int main()
{
    //Declaring pointer
    double *x;
    long int counter = 0;

    //starting infinite loop
    while(1)
    {
        x = xmalloc(1000000000);
        counter += 1;
        printf("We have allocated %ld gigabytes\n", counter);
    }

    return 0;
}
