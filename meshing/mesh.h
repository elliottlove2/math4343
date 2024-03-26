#ifndef H_MESH_H
#define H_MESH_H
#include "problem-spec.h"

struct node {
    int nodeno;
    double x;
    double y;
    double z;
    int bc;
};

struct edge {
    int edgeno;
    struct node *n[2];
    int bc;
};

struct elem {
    int elemno;
    struct node *n[3];
    struct edge *e[3];
    double ex[3], ey[3];
    double area;
};

struct mesh {
    struct node *nodes;
    struct edge *edges;
    struct elem *elems;
    int nnodes;
    int nedges;
    int nelems;
};

struct mesh *make_mesh(struct problems_spec *spec, double a);
void free_mesh(struct mesh *mesh);
#endif /*H_MESH_H*/
