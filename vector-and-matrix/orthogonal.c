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


    /*Within the loops we will need information on the current column of A, 
    the previous (orthogonalized) column, and the new orthogonalied column of A. */
    double *formerColumn;
    make_vector(formerColumn, m);
    double *currentColumn;
    make_vector(currentColumn, m);
    double *newColumn;
    make_vector(newColumn, m);
    /*The first column will be the q from earlier, the normalized first column of A.*/
    formerColumn = q;

    //This first loop will iterate through the n columns of A. 
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