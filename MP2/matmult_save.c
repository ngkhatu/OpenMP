#include <stdio.h>
#include <omp.h>

#define MATRIX_DIM 1000
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


omp_set_num_threads(omp_get_num_procs());
  /* Perform several rounds of Y = A x B */
for (n=0; n<NUM_ITER;  n++) {
	//#pragma omp parallel for default(shared) private(i,j,k)
	for (i=0; i<MATRIX_DIM; i++) 
		//#pragma omp parallel for default(shared) private(j,k)      
		for (j=0; j<MATRIX_DIM; j++) {
			Y[i][j] = 0.0;				//S1
			//sum = 0;
			
			//#pragma omp parallel for default(shared) reduction(+:sum)
			for (k=0; k<MATRIX_DIM; k++) {
	  			Y[i][j] = Y[i][j] + A[i][k] * B[k][j];		//S2
				//sum = sum + A[i][k] *B[k][j];
			}
			//Y[i][j] = sum;
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
