#include <stdio.h>
#include "sparse.h"
#include "array.h"


void sparse_unpack(double **a, int m, int n, int *Ap, int *Ai, double *Ax)
{
	int i, j, k;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			a[i][j] = 0.0;
		}
	}	
	for (j = 0; j < n; j++)
	{
		for (k = Ap[j]; k < Ap[j+1]; k++)
		{
			i = Ai[k];
			a[i][j] = Ax[k];
		}
	}
}

void sparse_pack(double **a, int m, int n, int *Ap, int *Ai, double *Ax)
{
	int k = 0;

	//Filling up Ap with -1 to indicate invalid entry. 
	for (int j = 0; j <= n; j++)
	{
		Ap[j] = -1;
	}

	for (int j = 0; j<n; j++)
	{
		for (int i = 0; i<m; i++)
		{
			if (a[i][j] != 0)
			{
				//storing nonzero values in Ax
				Ax[k] = a[i][j];
				//storing row index in Ai
				Ai[k] = i;

				//This condition checks to see if we are at the first 
				//nonzero entry of column j, in which case we 
				//will update Ap[j] to be k, the position (in Ax) of the first entry. 
				if (Ap[j] == -1)
				{
					Ap[j] = k;
				}

				//k is counting the number of elements in Ax
				k++;
			}
		}
	}

	//Filling in the (m+1)th entry of Ap with the number of elements in Ax.
	Ap[n] = k;
}
