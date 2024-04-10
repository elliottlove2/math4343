#include <stdio.h>
#include <stdlib.h>
#include "gauss-quad.h"
#include "array.h"

//show usage function, to inform users about the neccessary command line argument. 
void show_usage()
{
    printf("Usage: ./gauss-quad-demo n\n");
    printf("n: number of quadrature points, use n between 1 and 15.\n");
}

double f(double x)
{
    return 1 + x + x*x + x*x*x;
}

//main function will take command line arguments for the number of quadrature points. 
int main(int argc, char **argv)
{  
    int n;
    if (argc != 2)
    {
        show_usage();
        return EXIT_FAILURE;
    }
    n = atol(argv[1]);
    if ((n<= 0) || (n>15))
    {
        printf("Please choose n between 1 and 15.\n Exitting.\n");
        return EXIT_FAILURE;
    }
    printf("Using %d quadrature points.\n", n);
    
    //getting the nth quadrature table from gauss-quad.c
    struct Gauss_qdat *table;
    table = gauss_qdat(&n);

    //estimating the integral of f(x) on [-1,1], using n quadrature point. 
    double sum = 0;
    while (table -> w != -1)
    {
        sum += table -> w * f(table -> p);
        table++;
    }

    printf("The estimation for the integral of 1+x+x^2+x^3 on [-1,1] is %lf\n", sum);

    //estimating the integral on [2,5] using a change of variables. 
    sum = 0.0;
    table = 0;
    while (table -> w != -1)
    {
        sum += table -> w * f(((double)5/2 - (double)2/2) + ((double)5/2 - (double)2/2) * (table -> p));
        table++;
    }
    printf("The estimation for the integral of 1+x+x^2+x^3 on [2,5] is %lf\n", sum);
}


