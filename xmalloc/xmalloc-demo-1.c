#include<stdlib.h>
#include<stdio.h>
#include "xmalloc.h"

int main()
{
    //First we declare a pointer x 
    double *x;

    //Allocating and freeing 1,000 bytes
    printf("Allocating 1,000 bytes\n");
    x = xmalloc(125 * sizeof(double));
    free(x);
    printf("freed\n");

    //Attempt to allocate 0 bytes
    printf("Attempting to allocate 0 bytes\n");
    x = xmalloc(0);
    free(x);
    printf("The memory is freed. This message will not print since the program will exit on line 18.");

    return 0;
}

