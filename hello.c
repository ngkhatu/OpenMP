#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Use:
// setenv OMP_NUM_THREADS2 (3, 4, 8, etc)
// gcc -fopenmp hello.c -o hello


int main (int argc, char *argv[]) 
{
  int nthreads, tid;

 // tid = 0;
#pragma parallel private(nthreads, tid)
{
 tid = omp_get_thread_num();
 printf("Hello World from thread = %d\n", tid);
 
 //if(tid==0){
	#pragma omp master
	{
	nthreads= omp_get_num_threads();
	printf("Number of threads = %d\n", nthreads);
	}
	}
 
  
return 0;
}
