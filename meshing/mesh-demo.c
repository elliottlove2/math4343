#include <stdio.h>
#include <stdlib.h>
#include "problem-spec.h"
#include "mesh-to-eps.h"

static void do_demo(struct problem_spec *spec, double a, char *eps_filename)
{
	struct mesh *mesh = make_mesh(spec, a);
	printf("vertices = %d, edges = %d, elems = %d\n",
			mesh->nnodes, mesh->nedges, mesh->nelems);
	mesh_to_eps(mesh, eps_filename);
	free_mesh(mesh);
}

static void show_usage(char *progname)
{
	fprintf(stderr, "Usage: %s a\n", progname);
	fprintf(stderr, "    a = maximal triangle area\n");
}

int main(int argc, char **argv)
{
	struct problem_spec *square(void);
	struct problem_spec *triangle_with_hole(void);
	struct problem_spec *annulus(int n);
	void free_annulus(struct problem_spec *spec);
	struct problem_spec *three_holes(int n);
	void free_three_holes(struct problem_spec *spec);
	struct problem_spec *spec;
	char *endptr;
	double a;

	if (argc != 2) {
		show_usage(argv[0]);
		return EXIT_FAILURE;
	}

	a = strtod(argv[1], &endptr);
	if (*endptr != '\0' || a <= 0.0) {
		show_usage(argv[0]);
		return EXIT_FAILURE;
	}

	/* --- square() -------------------------------- */
	do_demo(square(), a, "square.eps");
	putchar('\n');

	/* --- triangle_with_hole() -------------------- */
	do_demo(triangle_with_hole(), a, "triangle-with-hole.eps");
	putchar('\n');

	/* --- annulus() ------------------------------- */
	spec = annulus(24);
	do_demo(spec, a, "annulus.eps");
	free_annulus(spec);
	putchar('\n');

	/* --- three_holes() ------------------------------- */
        TODO 

	return EXIT_SUCCESS;
}
