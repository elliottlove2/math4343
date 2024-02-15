#include "array.h"
#include <stdio.h>

double **hilbert_matrix(int n)
{
    double **H;
    make_matrix(H,n,n);
    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
        {
            H[i][j] = 1.0 / (1+i+j);
        }
    }

    return H;
}

int main()
{
    double **H;
    int n = 8;
    H = hilbert_matrix(n);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
            printf("%f ", H[i][j]);
        printf("\n");
    }
    free_matrix(H);

    return 0;
}
