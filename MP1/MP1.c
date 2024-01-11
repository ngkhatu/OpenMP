#include<stdio.h>
#include<omp.h>
//#include<time.h>
#include<stdio.h>

int main()
{
	// This is to reserve 8 cache blocks( assuming that each cache block is 64 bytes and the integer is 4 bytes)

	system("date");

	int A[128];
	int i=0;

	for(i=0;i<128;i++)
	{
		A[i]=i;
	}
	
	int j=0;
	// This directive is to indicate a parallel area, We set A as shared to make all threads access the same version of the array 
	#pragma omp parallel shared(A)
	{     
		// This directive tells the compiler to parallelize this loop
 		#pragma omp for nowait
		 for(i=0;i<8;i++)
		{   

			// This statement prints the number of parallel threads are currently running by your program 
			printf("Number of threads is : %d \n",omp_get_num_threads());
			int j;
			
			for(j=0; j< 1000000000;j++)
			{
				// We make sure that each thread write to a unique cache block
				A[i*16] = i * A[i*16] + 5; 
			}       
		}
	}
	system("date");

	return 0;
}

// 1 max thread: 23, 23, 23 seconds
// 2 max threads: 11, 11, 11 seconds
// 3 max threads: 9, 9, 9 seconds
// 4 max threads: 6, 6, 6 seconds
// 8 max threads: 6, 6, 6 seconds

