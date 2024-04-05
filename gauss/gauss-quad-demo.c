#include <stdio.h>
#include <stdlib.h>
#include "gauss-quad.h"

//show usage function, to inform users about the neccessary command line argument. 
void show_usage()
{
    printf("Usage: ./gauss-quad-demo n\n");
    printf("n: number of quadrature points\n");
}

//This function will return Pn(x) and P'n(x) where Pn is the nth legendre polynomial. 
double P(double x, int n)
{
   double Pcurrent;
   double Pprev; 
   double Pnew;
   double Pprime;
   double temp;
   Pcurrent = x;
   Pprev = 0;
   for (int i = 0; i<n+1; i++)
   {
    Pnew = ((2*i +1 )*x *Pcurrent - i * Pprev)/(i+1);
    Pprime = (i*x*Pcurrent - i * Pprev)/(x*x -1);

    temp = Pcurrent;
    Pcurrent = Pnew;
    Pprev = temp;
   }

   return Pcurrent, Pprime;
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
    printf("Using %ld quadrature points.", n);


    
}

