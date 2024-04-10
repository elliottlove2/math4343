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
    long n;
    if (argc != 2)
    {
        show_usage();
        return EXIT_FAILURE;
    }
    n = atol(argv[1]);
    if ((n<= 0) || (n>15))
    {
        printf("Please choose n between 1 and 15.\n Exitting.\n")
        return EXIT_FAILURE;
    }
    printf("Using %ld quadrature points.", n);
    
    //getting the nth quadrature table from gauss-quad.c
    //table -> x[j] gives jth coordinate, 
    //and table -> w[j] gives jth weight. 
    struct Gauss_qdat *table = gauss_qdat(&n);

    //estimating the integral of f(x) on [-1,1], using n quadrature point. 
    double sum = 0;
    double x = 0;
    double w = 0;
    for (int i = 0; i<n; i++)
    {
        x = table -> x[i];
        w = table -> w[i];
        sum += w * f(x);
    }
    printf("The estimation for the integral of 1+x+x^2+x^3 on [-1,1] is %lf", sum);

    //estimating the integral on [2,5] using a change of variables. 
}

