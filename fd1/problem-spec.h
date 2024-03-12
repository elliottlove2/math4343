#ifndef H_PROBLEM_SPEC_H
#define H_PROBLEM_SPEC_H

struct problem_spec {
        double a;                       // left end at $x = a$
        double b;                       // right end at $x = b$ 
        double (*ic)(double x);         // initial condition
        double (*bcL)(double t);        // left boundary condition
        double (*bcR)(double t);        // right boundary condition
        double (*u_exact)(double x, double t);  // exact solution, if any
};
#endif /* H_PROBLEM_SPEC_H */
