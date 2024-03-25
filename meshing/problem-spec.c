#include <stdio.h>
#include <math.h>
#include "array.h"
#include "problem-spec.h"

/*--- SQUARE --------------------------------------------------- */

struct problem_spec *square(void)
{
	static struct problem_spec_point points[] =  {
		{ 0,	0.0,	0.0,	FEM_BC_DIRICHLET },
		{ 1,	1.0,	0.0,	FEM_BC_DIRICHLET },
		{ 2,	1.0,	1.0,	FEM_BC_DIRICHLET },
		{ 3,	0.0,	1.0,	FEM_BC_DIRICHLET },
	};
	static struct problem_spec_segment segments[] = {
		{ 0,	0,	1,	FEM_BC_DIRICHLET },
		{ 1,	1,	2,	FEM_BC_DIRICHLET },
		{ 2,	2,	3,	FEM_BC_DIRICHLET },
		{ 3,	3,	0,	FEM_BC_DIRICHLET },
	};
	static struct problem_spec spec = {	// C99-style initialization!
		.points		= points,
		.segments	= segments,
		.holes		= NULL,	/* no holes */
		.npoints	= (sizeof points)/(sizeof points[0]),
		.nsegments	= (sizeof segments)/(sizeof segments[0]),
		.nholes		= 0,	/* no holes */
		.f		= NULL,
		.g		= NULL,
		.h		= NULL,
		.eta		= NULL,
		.u_exact	= NULL,
	};
	printf("domain is a square\n");
	return &spec;
}


/*--- Triangle with hole --------------------------------------- */

struct problem_spec *triangle_with_hole(void)
{
	static struct problem_spec_point points[] =  { // the points
		// triangle's vertices
		{ 0,	-1.0,	0.0,	FEM_BC_DIRICHLET },
		{ 1,	1.0,	0.0,	FEM_BC_DIRICHLET },
		{ 2,	0.0,	2.0,	FEM_BC_DIRICHLET },
		// hole's vertices
		{ 3,	-0.25,	0.25,	FEM_BC_DIRICHLET },
		{ 4,	+0.25,	0.25,	FEM_BC_DIRICHLET },
		{ 5,	+0.25,	1.0 ,	FEM_BC_DIRICHLET },
		{ 6,	-0.25,	1.0 ,	FEM_BC_DIRICHLET },
	};

	static struct problem_spec_segment segments[] = { // the segments
		// triangle's segments
		{ 0,	0, 1,	FEM_BC_DIRICHLET },
		{ 1,	1, 2,	FEM_BC_DIRICHLET },
		{ 2,	2, 0,	FEM_BC_DIRICHLET },
		// hole's segments
		{ 3,	3, 4,	FEM_BC_DIRICHLET },
		{ 4,	4, 5,	FEM_BC_DIRICHLET },
		{ 5,	5, 6,	FEM_BC_DIRICHLET },
		{ 6,	6, 3,	FEM_BC_DIRICHLET },
	};

	static struct problem_spec_hole holes[] = { // the hole's identifier
		{ 0.0, 0.75 }
	};

	static struct problem_spec spec = {  // C99-style initialization!
		.points		=  points,
		.segments	= segments,
		.holes		= holes,
		.npoints	= sizeof points / sizeof points[0],
		.nsegments	= sizeof segments / sizeof segments[0],
		.nholes		= sizeof holes / sizeof holes[0],
		.f			= NULL,
		.g			= NULL,
		.h			= NULL,
		.eta		= NULL,
		.u_exact	= NULL,
	};

	printf("domain is a triangle with hole\n");
	return &spec;
}


/*--- Annulus -------------------------------------------------- */

/* with a = 0.325 and b = 2a, the area of the domain is 0.9954921722 */
struct problem_spec *annulus(int n)
{
	double Pi = 4*atan(1);
	double a = 0.325, b = 2*a;
	struct problem_spec *spec = xmalloc(sizeof *spec);
	make_vector(spec->points, 2*n);
	make_vector(spec->segments, 2*n);
	make_vector(spec->holes, 1);

	for (int i = 0; i < n; i++) { // define the points
		double t = 2*i*Pi/n;
		spec->points[i].point_no = i;
		spec->points[i].x = a*cos(t);
		spec->points[i].y = a*sin(t);
		spec->points[i].bc = FEM_BC_DIRICHLET;
		spec->points[i+n].point_no = i+n;
		spec->points[i+n].x = b*cos(t);
		spec->points[i+n].y = b*sin(t);
		spec->points[i+n].bc = FEM_BC_DIRICHLET;
	}

	for (int i = 0; i < n; i++) { // define the segments
		spec->segments[i].segment_no = i;
		spec->segments[i].point_no_1  = i;
		spec->segments[i].point_no_2  = i+1;
		spec->segments[i].bc = FEM_BC_DIRICHLET;
		spec->segments[i+n].segment_no = i+n;
		spec->segments[i+n].point_no_1  = i+n;
		spec->segments[i+n].point_no_2  = i+n+1;
		spec->segments[i+n].bc = FEM_BC_DIRICHLET;
	}
	spec->segments[n-1].point_no_2 -= n;
	spec->segments[2*n-1].point_no_2 -= n;

	spec->holes[0].x = spec->holes[0].y = 0.0;	// the hole's identifier

	spec->npoints = 2*n;
	spec->nsegments = 2*n;
	spec->nholes = 1;
	spec->f = spec->g = spec->h = spec->eta = spec->u_exact = NULL;
	printf("domain is an annulus (really a %d-gon) "
			"of radii %g and %g\n", n, a, b);
	return spec;
}

void free_annulus(struct problem_spec *spec)
{
	if (spec != NULL) {
		free_vector(spec->points);
		free_vector(spec->segments);
		free_vector(spec->holes);
		free(spec);
	}
}


/*--- L-shape with 3 holes ------------------------------------- */

/* An L-shape region consisting of three 2x2 squares.  Each square has
 * a hole of radius r at its center.  The holes are actually n-gons,
 * where n is given as an argument.
 * When done, call free_three_holes() for free memory allocated here.
 *
 * with s = 0.64 and r = s/4, the area of the domain is 0.9875256842
*/
struct problem_spec *three_holes(int n)
{
        TODO 
	return spec;
}

void free_three_holes(struct problem_spec *spec)
{
        TODO	
}

