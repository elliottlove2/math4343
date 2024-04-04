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
    int n;
    printf("Input n:\n");
    scanf("%d", &n);
    H = hilbert_matrix(n);
    print_matrix("%.2lf", H, n, n);

    free_matrix(H);

    return 0;
}
