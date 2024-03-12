#include <stdio.h>
#include <math.h>
#include "problem-spec.h"
// heat1( ): quite a basic 1-D heat equation with exact solution
static double heat1_exact(double x, double t)
{
double Pi = 4*atan(1);
return exp(-Pi*Pi/4*t) * cos(Pi/2*x);
}
static double heat1_ic(double x)
{
return heat1_exact(x,0);
}
static double heat1_bcL(double t)
{
return heat1_exact(-1,t);
}
static double heat1_bcR(double t)
{
return heat1_exact(1,t);
}
struct problem_spec *heat1(void)
{
static struct problem_spec spec = { // C99-style initialization!
.a = -1.0,
.b = 1.0,
.ic = heat1_ic,
.bcL = heat1_bcL,
.bcR = heat1_bcR,
.u_exact = heat1_exact,
};
printf("problem heat1:\n");
return &spec;
}

//heat2
static double heat2_exact(double x, double t)
{
return erf(x / (2*sqrt(t)));
}
static double heat2_ic(double x)
{
return heat2_exact(x,0);
}
static double heat2_bcL(double t)
{
return heat2_exact(-1,t);
}
static double heat2_bcR(double t)
{
return heat2_exact(1,t);
}
struct problem_spec *heat2(void)
{
static struct problem_spec spec = { // C99-style initialization!
.a = -1.0,
.b = 1.0,
.ic = heat2_ic,
.bcL = heat2_bcL,
.bcR = heat2_bcR,
.u_exact = heat2_exact,
};
printf("problem heat2:\n");
return &spec;
}



//heat 3
static double heat3_ic(double x)
{
if (fabs(x) < .4)
    return 1;
else
    return 0;
}
static double heat3_bcL(double t)
{
return 0;
}
static double heat3_bcR(double t)
{
return 0;
}
struct problem_spec *heat3(void)
{
static struct problem_spec spec = { // C99-style initialization!
.a = -1.0,
.b = 1.0,
.ic = heat3_ic,
.bcL = heat3_bcL,
.bcR = heat3_bcR,
.u_exact = NULL,
};
printf("problem heat3:\n");
return &spec;
}

//heat 4
static double heat4_ic(double x)
{
return 0;
}
static double heat4_bcL(double t)
{
return 0;
}
static double heat4_bcR(double t)
{
return .8;
}
struct problem_spec *heat4(void)
{
static struct problem_spec spec = { // C99-style initialization!
.a = -1.0,
.b = 1.0,
.ic = heat4_ic,
.bcL = heat4_bcL,
.bcR = heat4_bcR,
.u_exact = NULL,
};
printf("problem heat4:\n");
return &spec;
}

