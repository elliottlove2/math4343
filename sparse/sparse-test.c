#include "sparse.h"
#include "array.h"
#include <stdio.h>
#include "xmalloc.h"
#include <math.h>
#include <stdbool.h>

int main()
{
    //creating a
    double **a;
    make_matrix(a, 4, 5);
    
    a[0][0] = 0.0; a[0][1] = 7.0; a[0][2] = 0.0; a[0][3] = 0.0; a[0][4] = 1.0;
    a[1][0] = 0.0; a[1][1] = 4.0; a[1][2] = 0.0; a[1][3] = 3.0; a[1][4] = 0.0;
    a[2][0] = 6.0; a[2][1] = 6.0; a[2][2] = 5.0; a[2][3] = 1.0; a[2][4] = 4.0;
    a[3][0] = 5.0; a[3][1] = 5.0; a[3][2] = 0.0; a[3][3] = 0.0; a[3][4] = 0.0;

    //counting the number of non-zero entries 
    int nnz = 0;

    printf("Printing the matrix a.\n");
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<5; j++)
        {
            printf("%g ", a[i][j]);
            if (a[i][j]!= 0.0)
            {
                nnz = nnz + 1;
            }
        }
        printf("\n");
    }

    printf("\n");
    printf("The number of non-zero entries is %d.\n", nnz);
   
    //Creating Ai, Ap, Ax
    double *Ax;
    int *Ai;
    int *Ap;
    make_vector(Ax, nnz);
    make_vector(Ap, 6);
    make_vector(Ai, nnz);

    //packing and printing the ccs
    printf("Printing the vectors Ax, Ai, and Ap\n");
    sparse_pack(a, 4, 5, Ap, Ai, Ax);
    print_vector("%g ", Ax, nnz);
    print_vector("%d ", Ai, nnz);
    print_vector("%d ", Ap, 6);

    printf("\n");

    //making b and unpacking into b. 
    double **b;
    make_matrix(b, 4, 5);
    sparse_unpack(b, 4, 5, Ap, Ai, Ax);

    printf("printing b \n");
    print_matrix("%g ", b, 4, 5);
    printf("\n"); 

    //using c to test
    double **c;
    make_matrix(c, 4, 5);
    bool success = true;
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<5; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
            if (c[i][j] != 0.0 )
            {
                success = false;
            }
        }
    }

    printf("Printing the matrix c=b-a, which should be the zero matrix\n");
    print_matrix("%g ", c, 4, 5);
    printf("\n");
    if (success == true)
    {
        printf("Successful packing and unpacking. \n\n");
    }
    else 
    {
        printf("failure\n\n");
    }

    //freeing all the memory. 
    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
    free_vector(Ap);
    free_vector(Ai);
    free_vector(Ax);
    
    return 0;


}

