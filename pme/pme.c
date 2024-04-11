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
    double old_guess = c;
    double new_guess = c;

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
    for (int j = 0; j< n+2; j++)
    {
        fprintf(fp, "%g %g %g\n", (double)k/steps, (double)j/(n+1), u[j]);
    }
}

//This function will calculate the error for the problem pme1. 

static double get_error(struct problem_spec *spec, double *u, int n, double t)
{
    double err = 0.0;
    for (int j=0; j<n+2; j++)
    {   
        double x = -1.0 + ((2.0)/(double)(n+1))*j;
        double diff = fabs(u[j] - spec -> u_exact(x,t));
        if (diff > err)
            err = diff;
    }

    return err;
    
}


//This will provide the user with instructions on using the program and the command line arguments necessary. 
static void show_usage(char *progname)
{
printf("Usage: %s T n s \n", progname);
printf("T: time domain is 0 < t < T \n");
printf("n: n is the number of grid points in the space dimension.\n");
printf("s: number of time slices.\n");
}


/* This pme1_sweep function will implement the Siedman Sweep method to solve the problem pme1.  */
static void pme(struct problem_spec *spec,
		double T, int n, int steps, int m, char *gv_filename)
{
	FILE *fp;
	double *u;
	double dx = (spec->b - spec->a)/(n+1.0);
	double dt = (double)T/steps;
	double r = dt/(2*(pow(dx, 2)));
	if ((fp = fopen(gv_filename, "w")) == NULL) {
		fprintf(stderr, "unable to open file `%s' for writing\n",
				gv_filename);
		return;
	}
	fprintf(fp, "# geomview script written by the function %s()\n",
			__func__);	// begin geomview script
	fprintf(fp, "{ appearance { +edge }\n");
	fprintf(fp, "MESH %d %d\n", n+2, steps+1);
	printf("%g < x < %g,  0 < t < %g,  dx = %g, dt = %g,  "
			"r = dt/dx^2 = %g\n",
			spec->a, spec->b, T, dx, dt, r);
	make_vector(u, n+2);

    //for loop to initialize u with initial conditions (time slice k=0)
	for (int j = 0; j < n+2; j++) {
		double x = -1.0 + ((2.0)/(n+1.0))*j;
		u[j] = spec->ic(x);
	}
	plot_curve(fp, u, n, steps, 0);

    //boundary conditions   
    for (int k = 1; k <= steps; k++)
    {
        //current time.
        double t = T*k / steps;
        //filling in left and right nodes with boundary conditions.
        u[0] = spec->bcL(t);
        u[n+1] = spec->bcR(t);

        //for loops to update the row u with the values for the new time slice. 
        //Since this is a Seidman Sweep scheme we go forward (up half a slice) and then
        //we go backwards (up another half slice with a reverse sweep motion.)

        //forward sweep
        for (int j = 1; j<= n; j++)
        {
            double RHS = r * pow(u[j-1], m) + u[j] - r * pow(u[j],m) + r * pow(u[j+1],m); 
            u[j] = newton(RHS, r, m);
        }
        //reverse sweep
        for (int j = n; j>= 1; j--)
        {
            double RHS = r * pow(u[j-1], m) + u[j] - r*pow(u[j], m) + (r * pow(u[j+1], m));
            u[j] = newton(RHS, r, m);
        }

        plot_curve(fp, u, n, steps, k);
	}   


	fprintf(fp, "}\n");	// end geomview script
	fclose(fp);
	printf("geomview script written to file %s\n", gv_filename);
	if (spec->u_exact != NULL) {	
		double err = get_error(spec, u, n, T);
		printf("max error at time %g is %g \n", T, err);
	}
	free_vector(u);
	putchar('\n');
}






/*The main function requires three arguments, T n and s. 
T is the upper end of the time range,
n is the number of grid points in the x direction,
s is the number of steps in the time direction.  */
int main(int argc, char **argv){
    struct problem_spec *pme1(void);
    struct problem_spec *pme2(void);
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

   pme(pme1(), T, n, s, m, "im1.gv");
   pme(pme2(), T, n, s, m, "im2.gv");

   return EXIT_SUCCESS;

}
