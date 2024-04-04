#include "sparse.h"
#include "array.h"
#include <stdio.h>
#include "xmalloc.h"

int main()
{
    //creating a
    double **a = malloc(4 * sizeof(double *));
    for (int i = 0; i < 4; i++) 
    {
        a[i] = malloc(5 * sizeof(double));
    }   
    
    a[0][0] = 0.0; a[0][1] = 7.0; a[0][2] = 0.0; a[0][3] = 0.0; a[0][4] = 1.0;
    a[1][0] = 0.0; a[1][1] = 4.0; a[1][2] = 0.0; a[1][3] = 3.0; a[1][4] = 0.0;
    a[2][0] = 6.0; a[2][1] = 6.0; a[2][2] = 5.0; a[2][3] = 1.0; a[2][4] = 4.0;
    a[3][0] = 5.0; a[3][1] = 5.0; a[3][2] = 0.0; a[3][3] = 0.0; a[3][4] = 0.0;

    //counting the number of non-zero entries 
    int nnz = 0;
    
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<5; j++)
        {
            printf("%g", a[i][j]);
            if (abs(a[i][j]>.0001))
            {
                nnz = nnz + 1;
            }
        }
        printf("\n");
        printf("%d", nnz);
    }
    printf("%d", nnz);
    printf("%d", nnz);

    //Creating Ai, Ap, Ax
    double *Ax;
    int *Ai;
    int *Ap;
    make_vector(Ax, nnz);
    make_vector(Ap, 6);
    make_vector(Ai, nnz);

    sparse_pack(a, 4, 5, Ap, Ai, Ax);
    print_vector("%g", Ax, nnz);
    print_vector("%d", Ai, nnz);
    print_vector("%d", Ap, 6);

    for (int i = 0; i < 4; i++)
    {
        free(a[i]);
    }
    free(a);


    return 0;


}

