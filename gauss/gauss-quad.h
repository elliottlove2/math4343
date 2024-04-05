/* gauss-quad.h
 *
 * Rouben Rostamian <rostamian@umbc.edu>
 * 2011-05-01
*/

#ifndef H_GAUSS_QUAD_H
#define H_GAUSS_QUAD_H

struct Gauss_qdat {
	double p;		// point
	double w;		// weight
};

struct Gauss_qdat *gauss_qdat(int *n);

#endif /* H_GAUSS_QUAD_H */
