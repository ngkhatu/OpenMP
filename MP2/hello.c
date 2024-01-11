#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


//export OMP_NUM_THREADS=2



int main (int argc, char *argv[]) 
{
	int nthreads, tid;
	
	nthreads = omp_get_num_threads();
	printf("Initial # of threads: %d\n", nthreads);

omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel private(nthreads, tid)
{
	tid = omp_get_thread_num();
	printf("Hello World from thread = %d\n", tid);
	//nthreads= omp_get_num_threads();
	//printf("Number of threads = %d\n", nthreads);


	#pragma omp master
	{
		if(tid==0){
			nthreads= omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
	}

}
  
	return 0;
}
