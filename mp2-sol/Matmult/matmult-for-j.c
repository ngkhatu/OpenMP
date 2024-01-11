#include <stdio.h>

#define MATRIX_DIM 300
#define NUM_ITER 10 
/* Try the problems with higher value of MATRIX_DIM and NUM_ITER */

double A[MATRIX_DIM][MATRIX_DIM], 
  B[MATRIX_DIM][MATRIX_DIM], 
  Y[MATRIX_DIM][MATRIX_DIM],
  sum;

int n, i, j, k;


int main() 
{
  /* Initialize Matrices A and B */
  for (i=0; i<MATRIX_DIM; i++) {
    for (j=0; j<MATRIX_DIM; j++) {
      A[i][j] = i / (double) MATRIX_DIM;
      B[i][j] = i*i / (double) (MATRIX_DIM * MATRIX_DIM);
    }
  }


  /* Perform several rounds of Y = A x B */
  for (n=0; n<NUM_ITER;  n++) {
    for (i=0; i<MATRIX_DIM; i++) {
#pragma omp parallel for default(shared)
      for (j=0; j<MATRIX_DIM; j++) {
	Y[i][j] = 0.0;
	for (k=0; k<MATRIX_DIM; k++) {
	  Y[i][j] = Y[i][j] + A[i][k] * B[k][j];
	}
      }
    }
  }

  /* Print out the sum of elements of Y */
  sum = 0;
  for (i=0; i<MATRIX_DIM; i++) {
    for (j=0; j<MATRIX_DIM; j++) {
      sum = sum + Y[i][j];
    }
  }
  printf("Sum = %f\n", sum);
}
