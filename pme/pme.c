#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "problem-spec.h"
#include "problem-spec.c"



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


//This function will calculate the error for the problem pme1. 
static get_error(struct problem_spec *spec, double *u, int n, double T)
{
        double relative = 0;
        double absolute = 0;

}


//This will provide the user with instructions on using the program and the command line arguments necessary. 
static void show_usage(char *progname)
{
printf("Usage: ./%s T n s \n", progname);
printf("T: time domain is 0 < t < T ");
printf("n: n is the number of grid points in the space dimension.");
printf("s: number of time slices. ");
}


/* This pme1_sweep function will implement the Siedman Sweep method to solve the problem pme1. */
static void pme1_sweep(struct problem_spec *spec, double T, int n, int s)
{
    //We will store the solution in an n x s matrix called u.
    double u[n][s];
    double tstep = T/s;
    double xstep = 2/n;

    //
    

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




}
