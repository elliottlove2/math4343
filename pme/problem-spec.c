#include <stdio.h>
#include <math.h>
#include "problem-spec.h"


//This function returns barenblatt's solution to the pme at a point (x,t)

static double barrenblatt (double x, double t, double m, double c, double delta)
{
    double beta, alpha, gamma, result, bracket;
    beta = 1 / (m+1);
    alpha = 1/ (m-1);
    gamma = (m-1)/(2 * m * (m+1));
    bracket = ( c- gamma * pow((x/ (pow(t+delta, beta) ) ), 2));
    bracket = (bracket >= 0 ? bracket : 0);

    result = 1/(pow(t+delta, beta)) * (pow(bracket, alpha));
    return result;
}

//This function provides an exact solution at points (x,t), dependent on choice of c, m, and delta.
//Currently we have c = sqrt(3)/15, delta = 1/75, and m = 3.

static double pme1_exact(double x, double t)
{
    double c = sqrt(3)/15, delta = 1.0/75;
    return barrenblatt(x, t, 3, c, delta);
}

//Next we will define some functions to extract initial conditions. This is for the "pme1" problem on page 288 of the textbook.


//This function gives us the initial condition at t=0.
static double pme1_ic(double x){
    return pme1_exact(x, 0);
}


//This function provides the boundary condition on the left.
static double pme1_bcL(double t){
    return pme1_exact(-1, t);
}

//This function provides the boundary condition on the right. 
static double pme1_bcR(double t){
    return pme1_exact(1, t);
}

/* This structure contains the details of the problem, interval of interest, initial and boundary conditions,
and the exact solution from Barrenblat's solution for the sake of error testing. */ 
struct problem_spec *pme1(void){
    static struct problem_spec spec = {
        .a = -1.0,
        .b = 1.0,
        .ic = pme1_ic,
        .bcL = pme1_bcL,
        .bcR = pme1_bcR,
        .u_exact = pme1_exact,
    };
    printf("\n pme1.\n");
    return &spec;
}

//NOT COMPLETED
struct problem_spec *pme1(void){
    static struct problem_spec spec = {
        .a = -1.0,
        .b = 1.0,
        .ic = pme1_ic,
        .bcL = pme1_bcL,
        .bcR = pme1_bcR,
        .u_exact = pme1_exact,
    };
    printf("\n pme1.\n");
    return &spec;
}


