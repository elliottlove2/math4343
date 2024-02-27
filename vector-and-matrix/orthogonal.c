#include <math.h>
#include <stdlib.h>
#include<stdio.h>
#include "array.h"

// In this program we will implement the Gram Schmidt algorithm for orthogonalizing matrices. 


double dot(double *v, double *u, int n)
{
    double result;
    for (int i = 0; i<n; i++)
    {
        result += v[i]*u[i];
    }
    return result;
}

void normalize(double *v, int n)
{
    double norm;
    double sumOfSquares;

    for (int i=0; i < n; i++)
    {
        sumOfSquares += v[i]*v[i];
    }

    norm = sqrt(sumOfSquares);

    for (int i = 0; i < n; i++)
    {
        v[i] = v[i] / norm;
    }
}


void gramSchmidt(double **A, int m, int n)
{
    //This function takes in A and changes A into an orthogonal matrix.
    //First we will normalize the columns of A
    double *q;
    make_vector(q, m);

    //Normalizing the first column
    for (int i = 0; i < m; i++)
    {
        q[i] = A[i][0];
    }
    normalize(q, m);
    for (int i = 0; i < m; i++)
    {
        A[i][0] = q[i];
    }


    /*Suppose the unchanged k_th column of A is x_k, and the new column is q_k.
    Then q_k is equal to x_k - p_{k-1}, normalized. 
    To do this calculation, at each step we will need the current column vector, a vector to store the new column,
    and the vector p. The vector p will be calculated by storing the jth column of A as q, then adding (x_k * q)q to p. 
    Once we do this process for all columns of A up to q_{k-1}, we will have p. */

    //Initializing p, q, and x.
    double *q;
    make_vector(q, m);
    double *x;
    make_vector(x, m);
    double *p;
    make_vector(p, m);

    // With this loop we are iterating through the columns of A. 
    for (int i = 1; i < n; i++)
    {
       
    }




}


int main()
{
    //We will store the orthogonlized result in the matrix m
    double **m;
    make_matrix(m, 4, 3);

    //Defining a to test the algorithm
    double a[3][4] = {
        {1, -1, 4},
        {1, 4, -2},
        {1, 4, 2},
        {1, -1, 0}
    };
    
    

    return 0;
}