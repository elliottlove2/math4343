#include <math.h>
#include <stdlib.h>
#include<stdio.h>
#include "array.h"

// In this program we will implement the Gram Schmidt algorithm for orthogonalizing matrices. 


double dot(double *v, double *u, int n)
{
    double result = 0;
    for (int i = 0; i<n; i++)
    {
        result += v[i]*u[i];
    }
    return result;
}

void normalize(double *v, int n)
{
    double norm;
    double sumOfSquares = 0;

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
    //This function takes in a mxn matrix A and changes A into an orthogonal matrix.

    double *firstColumn;
    make_vector(firstColumn, m);

    //Normalizing the first column
    for (int i = 0; i < m; i++)
    {
        firstColumn[i] = A[i][0];
    }
    normalize(firstColumn, m);
    for (int i = 0; i < m; i++)
    {
        A[i][0] = firstColumn[i];
    }


    /*Suppose the unchanged k_th column of A is x_k, and the new column is q_k.
    Then q_k is equal to x_k - p_{k-1}, normalized. 
    To do this calculation, at each step we will need the current column vector, a vector to store the new column,
    and the vector p. The vector p will be calculated by storing the jth column of A as q, then adding (x_k * q)q to p. 
    Once we do this process for all columns of A up to q_{k-1}, we will have p. */

    //Initializing p and x.
    double *x;
    make_vector(x, m);
    double *p;
    make_vector(p, m);
    for (int j = 0; j < m; j++)
    {
        p[j] = 0;
    }

    // With this loop we are iterating through the columns of A. 
    for (int i = 1; i < n; i++)
    {
        //x is the ith column of A
        for (int j=0; j < m; j++)
        {
            x[j] = A[j][i];
        }
        //These loop creates a vector p
        for (int c = 0; c < i; c++)
        {
            double *q;
            make_vector(q, m);

            for (int j = 0; j < m; j++)
            {
                q[j] = A[j][c];
            }
            for (int j = 0; j < m; j++)
            {    
                p[j] += (dot(x, q, m)) * q[j];
            }

            free_vector(q);
        }


        double *newVector;
        make_vector(newVector, m);
        for (int j = 0; j < m; j++)
        {
            newVector[j] = x[j] - p[j];
        }
        normalize(newVector, m);
        for (int j = 0; j < m; j++)
        {
            A[j][i] = newVector[j];
        }
        free_vector(newVector);
    }

    free_vector(p);
}

int main()
{
    //We will store the orthogonlized result in the matrix m
    double **m;
    make_matrix(m, 4, 3);

    //Defining a to test the algorithm
    double **a;
    make_matrix(a, 4, 3);
    a[0][0] = 1; a[0][1] = -1; a[0][2] = 4;
    a[1][0] = 1; a[1][1] = 4;  a[1][2] = -2;
    a[2][0] = 1; a[2][1] = 4;  a[2][2] = 2;
    a[3][0] = 1; a[3][1] = -1; a[3][2] = 0;

    gramSchmidt(a, 4, 3);
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 3; j++) 
            printf("%.2lf ", a[i][j]);
        printf("\n");
    }
    
    return 0;
}
