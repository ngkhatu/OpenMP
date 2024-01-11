#include <stdio.h>
#include <omp.h>
#include <math.h>

#define MATRIX_DIM 1000
#define NUM_ITER 10 
/* Try the problems with higher value of MATRIX_DIM and NUM_ITER */

double amax, my_amax ;
double A[MATRIX_DIM][MATRIX_DIM], 
  B[MATRIX_DIM][MATRIX_DIM], 
  Y[MATRIX_DIM][MATRIX_DIM],
  sum;

int n, i, j, k;
/*
double abs_max(amax, A[i][j], B[i][j])
{
  double u, v, w; 
  u = fabs(amax);
  v = fabs(A[i][j]);
  w = fabs(B[i][j]);
  if (u<v) {
    if (v<w) amax = w;
    else amax = v;
  }
  else {
    if (u<w)amax = w;
    else amax = u;
  }
}
*/

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


  /* Find the sum of elements of Y */
  sum = 0;
#pragma omp parallel for default(shared) private(i,j) reduction(+:sum)
  for (i=0; i<MATRIX_DIM; i++) {
    for (j=0; j<MATRIX_DIM; j++) {
      sum = sum + A[i][j];
    }
  }
  printf("Sum = %f\n", sum);

  /* Find absolute maximum of elements in matrix Y */
  amax = 0;
my_amax = 0.0;


#pragma omp parallel shared(amax) private(i, j) firstprivate(my_amax)
{
#pragma omp for
{
for (i=0; i<MATRIX_DIM; i++) {
    for (j=0; j<MATRIX_DIM; j++) {
      my_amax = abs_max(my_amax, A[i][j], B[i][j]);
}
}
}
	#pragma omp critical
	{	
	amax = abs_max(amax, my_amax, amax);
	}
}  
/*
for (i=0; i<MATRIX_DIM; i++) {
    for (j=0; j<MATRIX_DIM; j++) {
      //amax = abs_max(amax, A[i][j], B[i][j]);
	double u, v, w; 
  u = fabs(amax);
  v = fabs(A[i][j]);
  w = fabs(B[i][j]);
  if (u<v) {
    if (v<w) amax = w;
    else amax = v;
  }
  else {
    if (u<w)amax = w;
    else amax = u;
  }
    }
  }
*/
  printf("- sum of matrix = %f\n", sum);
  printf("- absmax of matrix = %f\n", amax);
}
