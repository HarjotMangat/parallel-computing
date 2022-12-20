/*
* Harjot Mangat
* EECS 245 - Parallel Computing
* Lab 02 - OpenMP
* Parallel Sum with static scheduling
*/
/*int argc, char* argv[]*/
// OpenMP header
#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define N 100000
#define THREADS 2
int main()
 {
	omp_set_num_threads(THREADS);
	int x[N] = {};
	int y[N] = {};
	int* T = new int[THREADS + 1];
	T[0] = 0;
	std::fill_n(x, N, 1);
	double t1, t2;
	
	t1 = omp_get_wtime();
/*#pragma omp parallel for schedule(static, 4)
	{
		const int ithread = omp_get_thread_num();
		const int nthreads = omp_get_num_threads();
		int j = 0;
		//#pragma omp parallel for schedule(static,4)
		for (int i = 0; i<N; i++)
		{
			j += x[i];
			//std::cout << j << std::endl ;
			sum[i] = j;
		}
		
	}*/

	int sum = 0;
	//parallel partial prefix sum
#pragma omp parallel for schedule(static) reduction(+:sum)
	for (int i = 0; i < N; i++) {
		sum += x[i];
		y[i] = sum;
		T[omp_get_thread_num() + 1] = sum;
	}
	// prefix sum on T
	for (int i = 1; i < THREADS; i++) {
		T[i] += T[i - 1];
		//std::cout << suma[i] << std::endl;
	}
	//Every thread adds T[threadID] to its elements
#pragma omp parallel for schedule(static) //reduction(+:y[i])
	for (int i = 0; i < N; i++) {
		y[i] += T[omp_get_thread_num()];
	}
	// Print out the final resulting prefix sum
	for (int i = 0; i < N; i++) {
		std::cout << y[i] << std::endl;
	}

	std::cout << std::endl;
	t2 = omp_get_wtime();
	printf("Time = % g\n", t2-t1);
}
