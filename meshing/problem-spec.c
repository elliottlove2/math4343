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
	double Pi = 4*atan(1);
	//defining s and r. s is the the side length of each square. 
	//The radius of the inner circles are r = s/4. 
	//Note that the centers of the holes lie at the points (+- s/2, +-s/2).
    double s = .64;
	double r = s/4;
	struct problem_spec *spec = xmalloc(sizeof *spec);

	make_vector(spec->points, 3*n + 6);
	make_vector(spec->segments, 3*n + 6);
	make_vector(spec->holes, 3);

	/* Defining the points for the vertices and for the holes.
	The first 3n points will be for the three holes, the last 6 points will be the square vertices.
	*/
	for(int i = 0; i < n; i++)
	{
		//theta will be the current angle for each circle.
		double theta = 2 * Pi * i / n;
		spec -> points[i].point_no = i;
		spec -> points[i + n].point_no = i + n;
		spec -> points[i + 2*n].point_no = i + 2*n;

		spec->points[i].x = r*cos(theta) - s/2;
		spec->points[i].y = r*sin(theta) + s/2;
		spec->points[i + n].x = r*cos(theta) -s/2;
		spec->points[i + n].y = r*sin(theta) - s/2;
		spec->points[i + 2*n].x = r*cos(theta) + s/2;
		spec->points[i + 2*n].y = r*sin(theta) + s/2;

		spec->segments[i].bc = FEM_BC_DIRICHLET;
		spec->segments[i + n].bc = FEM_BC_DIRICHLET;
		spec->segments[i + 2*n].bc = FEM_BC_DIRICHLET;
	}
	
	for(int i = 3*n; i<3*n + 6; i++)
	{
		spec -> points[i].point_no = i;
		spec -> points[i].bc = FEM_BC_DIRICHLET;
	}

	spec -> points[3*n].x = -s;
	spec -> points[3*n].y = s;
	spec -> points[3*n + 1].x = -s;
	spec -> points[3*n + 1].y = -s;
	spec -> points[3*n + 2].x = 0;
	spec -> points[3*n + 2].y = -s;
	spec -> points[3*n + 3].x = 0;
	spec -> points[3*n + 3].y = 0;
	spec -> points[3*n + 4].x = s;
	spec -> points[3*n + 4].y = 0;
	spec -> points[3*n + 5].x = s;
	spec -> points[3*n + 5].y = s;

	//Defining the segments
	for (int i = 0; i < n; i++)
	{
		spec->segments[i].segment_no = i;
		spec->segments[i].point_no_1  = i;
		spec->segments[i].point_no_2  = i+1;
		spec->segments[i].bc = FEM_BC_DIRICHLET;
		spec->segments[i+n].segment_no = i+n;
		spec->segments[i+n].point_no_1  = i+n;
		spec->segments[i+n].point_no_2  = i+n+1;
		spec->segments[i+n].bc = FEM_BC_DIRICHLET;
		spec->segments[i+n].segment_no = i+2*n;
		spec->segments[i+n].point_no_1  = i+2*n;
		spec->segments[i+n].point_no_2  = i+2*n+1;
		spec->segments[i+n].bc = FEM_BC_DIRICHLET;
	}
	spec->segments[n-1].point_no_2 -= n;
	spec->segments[2*n-1].point_no_2 -= n;
	spec->segments[3*n-1].point_no_2 -= n;

	//Defining the holes. 
	spec -> holes[0].x = -s/2;
	spec -> holes[0].y = s/2;
	spec -> holes[1].x = -s/2;
	spec -> holes[1].y = -s/2;
	spec -> holes[2].x = s/2;
	spec -> holes[2].y = -s/2;

	spec->npoints = 3*n + 6;
	spec->nsegments = 3*n + 6;
	spec->nholes = 3;

	spec->f = spec->g = spec->h = spec->eta = spec->u_exact = NULL;
	printf("domain is an L with 3 holes (which are really %d-gons) "
		"with radius %g\n", n, r);
	return spec;
}

void free_three_holes(struct problem_spec *spec)
{
     if (spec != NULL) {
		free_vector(spec->points);
		free_vector(spec->segments);
		free_vector(spec->holes);
		free(spec);
	}
}

