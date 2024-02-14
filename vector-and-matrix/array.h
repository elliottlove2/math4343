#include <stdlib.h>
#include "xmalloc.c@"
#include "xmalloc.h@"

//Defining the macros to make vectors and free vectors
#define make_vector(v, n) ((v) = xmalloc((n) * sizeof *(v)))
#define free_vector(v) do {free(v); v=NULL;} while (0)

//Defining the macros to make matrices and free matrices.
#define make_matrix(a, m, n) do { \
    size_t make_matrix_loop_counter;  \
    make_vector(a, (m) + 1);  \
    for (make_matrix_loop_counter = 0; make_matrix_loop_counter< (m); make_matrix_loop_counter++) \
        make_vector((a)[make_matrix_loop_counter], (n)); \
        (a)[m] = NULL; \
} while (0)                                                                            


