#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "problem-spec.h"
#include "array.h"




//This function approximates the solution to x + r x^m = c, using Newton's method. 

static double newton(double c, double r, int m)
{
    //We need to define an error allowance to tell the program when the approximation is good enough
    double allowed_error = .001;
    double error = 1.0;

    //Using the magnitude of c as an initial guess. I have not explored which potential intial guesses might optimize this algorithm. 
    double old_guess = fabs(c);
    double new_guess = fabs(c);

    //While loop to iteratively adjust guess towards the solution
    while(error > allowed_error){
        new_guess = old_guess - (old_guess + r * pow(old_guess, m) - c) / (r * m * pow(old_guess, m-1) + 1);
        error = fabs(new_guess - old_guess);
        old_guess = new_guess;
    }

    return old_guess;
}

//This file writes the geomview script
static void plot_curve(FILE *fp, double *u, int n, int steps, int k)
{
    for (int j = 0; j< n + 2; j++)
    {
        fprintf(fp, "%g %g %g\n", (double)k/steps, (double)j/(n+1), u[j]);
    }
}


//This function will calculate the error for the problem pme1. 

static get_error(struct problem_spec *spec, double *u, int n, double T)
{
       double err = 0.0;
       for (int j=0; j<n+2; j++)
       {
            double x = -1 + (2/n)*j;
            double diff = fabs(u[j] - spec -> u_exact(x,T));
            if (diff > err)
                err = diff;
       }
}


//This will provide the user with instructions on using the program and the command line arguments necessary. 
static void show_usage(char *progname)
{
printf("Usage: ./%s T n s \n", progname);
printf("T: time domain is 0 < t < T ");
printf("n: n is the number of grid points in the space dimension.");
printf("s: number of time slices. ");
}


/* This pme1_sweep function will implement the Siedman Sweep method to solve the problem pme1.  */
static void pme1_sweep(struct problem_spec *spec, double T, int n, int s, int m, char *gv_filename)
{
    //We will store the solution in an 2n x 2s matrix called u. nx2s is the dimension because the siedman sweep uses 1/2 time steps.
    double **u;
    make_matrix(u, n, 2*s);

    //Time step and space step
    double tstep = T/2*s;
    double xstep = 2/n;
    double r = (tstep*2)/(2*(xstep)*(xstep));
    FILE *fp;

    //geomview stuff
    if ((fp = fopen(gv_filename, "w"))==NULL)
    {
        fprintf(stderr, "unable to open file '%s' for writing \n", gv_filename);
        return;
    }



    //We will fill u[x][t] with the initial conditions and boundary conditinos from the problem spec structure.
    for (int j = 0; j < n; j++)
    {
        double x = -1.0 + (j * xstep);
        u[j][0] = spec -> ic(x);
    }
    for (int j = 0; j< 2 * s && (j%2 == 0); j++)
    {
        double t = j * tstep;

        u[0][j] = spec -> bcL(t);
        u[n-1][j] = spec -> bcR(t);
    }

    u[0][2*s-1] = spec -> bcL(tstep * (2*s-1));
    u[n-1][2*s-1] = spec -> bcR(tstep * (2*s-1));

    //Now we can fill in the rest of u with the Seidman Sweep iterations. 
    for (int j = 1; j < n-1; j++)
    {
        for (int  k = 1; k < 2 * s -1; k++)
        {
            double RHS;
            RHS = r * pow(u[j-1][k+1] , m) + u[j][k] - r * pow((u[j][k]), m) + r*pow(u[j+1][k], m);
            u[j][k] = newton(RHS, r, m);
        }
    }


}

/*The main function requires three arguments, T n and s. 
T is the upper end of the time range,
n is the number of grid points in the x direction,
s is the number of steps in the time direction.  */
int main(int argc, char **argv){
    struct problem_spec *pme1(void);
    char *endptr;
    double T;
    int n;
    int s;
    int m = 3;
    if (argc != 4){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }
    T = strtod(argv[1], &endptr);
    if (*endptr != '\0' || T <= 0.0){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }
    n = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || n<1){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }
    s = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || s < 0){
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }

   // pme1_sweep(pme1(), T, n, s, m, );

}
