/*
* Harjot Mangat
* EECS 245 - Parallel Computing
* Lab 02 - OpenMP
* Parallel Sum with Dynamic scheduling
*/
/*int argc, char* argv[]*/



// OpenMP header
#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define N 16000
#define THREADS 4
int main()
{
	omp_set_num_threads(THREADS);
	//int ThreadID = omp_get_thread_num();
	int x[N] = {};
	int y[N] = {};
	int* T = new int[THREADS + 1];
	T[0] = 0;
	std::fill_n(x, N, 1);
	double t1, t2;
	int sub_array_len = N / THREADS;
	t1 = omp_get_wtime();

	int sum = 0;
	
	//parallel partial prefix sum
#pragma omp parallel for schedule(dynamic, sub_array_len) private(sum)
	for (int i = 0; i < N; i++) {
		sum += x[i];
		y[i] = sum;
		//DEBUG: Use below command for debugging this loop
		std::cout << "for index " << i << ' ' << omp_get_thread_num() << "  calculated  " << y[i] << std::endl;
		T[omp_get_thread_num()+1] = y[i];
	}

	//DEBUG: Below loop outputs array T before simple prefix sum
	std::cout << std::endl << "Array T" << std::endl;
	for (int i = 0; i < THREADS; i++) {
		std::cout << T[i] << std::endl;
	}

	//DEBUG: Below loop outputs Array y with the partial prefix sum
	std::cout << std::endl << "Partial sum on Array y" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << y[i] << std::endl;
	}
	std::cout << std:: endl;
	
	// prefix sum on T
	for (int i = 1; i < THREADS; i++) {
		T[i] += T[i-1];
	}
	
	//DEBUG: Below loop outputs array T after performing Prefix sum
	std::cout << std::endl << "Array T after Prefix sum" << std::endl;
	for (int i = 0; i < THREADS; i++) {
		std::cout << T[i] << std::endl;
	}
	std::cout << std::endl;
	//Every thread adds T[threadID] to its elements
#pragma omp parallel for schedule(static, sub_array_len)
	for (int i = 0; i < N; i++) {
		sum = y[i] + T[omp_get_thread_num()];
		y[i] = sum;
	}
	// Print out the final resulting prefix sum
	for (int i = 0; i < N; i++) {
		std::cout << y[i] << std::endl;
	}

	std::cout << std::endl;
	t2 = omp_get_wtime();
	printf("Time = % g\n", t2 - t1);
}
