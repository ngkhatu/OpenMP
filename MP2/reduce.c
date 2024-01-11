#include <stdio.h>
#include <omp.h>

#define MATRIX_DIM 9000
#define NUM_ITER 10 
/* Try the problems with higher value of MATRIX_DIM and NUM_ITER */

double A[MATRIX_DIM][MATRIX_DIM], 
  B[MATRIX_DIM][MATRIX_DIM], 
  Y[MATRIX_DIM][MATRIX_DIM],
  sum, amax, my_amax;

int n, i, j, k;

double abs_max(x, y, z)
{
  double u, v, w; 
  u = fabs(x);
  v = fabs(y);
  w = fabs(z);
  if (u<v) {
    if (v<w)
      return w;
    else 
      return v;
  }
  else {
    if (u<w)
      return w;
    else
      return u;
  }
}

int main() 
{

  /* Initialize Matrices A and B */
  for (i=0; i<MATRIX_DIM; i++) {
    for (j=0; j<MATRIX_DIM; j++) {
      A[i][j] = i / (double) MATRIX_DIM;
      B[i][j] = i*i / (double) (MATRIX_DIM * MATRIX_DIM);
    }
  }

omp_set_num_threads(4);
// 2.327, 1.982, 1.840, 1.779
  /* Find the sum of elements of Y */
  sum = 0;
#pragma omp parallel for default(shared) private(i,j) reduction(+:sum)
  for (i=0; i<MATRIX_DIM; i++) {
    for (j=0; j<MATRIX_DIM; j++) {
      sum = sum + A[i][j];
    }
  }
  printf("Sum = %f\n", sum);


//---------------------------------------------------------
amax = 0;
my_amax = 0.0;
#pragma omp parallel shared(amax) private(i, j) firstprivate(my_amax)
{
 /* Find absolute maximum of elements in matrix Y */
#pragma omp for
  for (i=0; i<MATRIX_DIM; i++) {
    for (j=0; j<MATRIX_DIM; j++) {
      //amax = abs_max(amax, A[i][j], B[i][j]);
	my_amax = abs_max(my_amax, A[i][j], B[i][j]);
    }
  }

#pragma omp critical
{	
	amax = abs_max(amax, my_amax, amax);
}

}

//------------------------------------------------------

  printf("- sum of matrix = %f\n", sum);
  printf("- absmax of matrix = %f\n", amax);

}
