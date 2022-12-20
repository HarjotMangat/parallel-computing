/* Harjot Mangat
*  EECS 245 - Parallel Computing
*  Implementation of the kernel we covered in class
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
//#include <device_functions.h>

#include <stdio.h>
#include <iostream>
//#include "kernel.h"

#define N 10000
#define BLOCK_SIZE 7
#define RADIUS 3
#define thread_count 55
#define block_count 10


float milliseconds = 0;



__global__ void stencil_1d(int *in, int *out) {
    __shared__ int temp[BLOCK_SIZE + 2*RADIUS];
    int gindex = threadIdx.x + blockIdx.x * blockDim.x;
    int lindex = threadIdx.x + RADIUS;

    temp[lindex] = in[gindex];
    if (threadIdx.x < RADIUS ) {
        temp[lindex - RADIUS] = in[gindex];
        temp[lindex + BLOCK_SIZE ] = in[gindex + BLOCK_SIZE];
    }

    __syncthreads();

    int result = 0;
    for (int offset = -RADIUS; offset <= RADIUS; offset++)
        result += temp[lindex + offset];

    out[gindex] = result;
}


void start_timer(cudaEvent_t* start) {
    cudaEventCreate(start);
    cudaEventRecord(*start);
}


float stop_timer(cudaEvent_t* start, cudaEvent_t* stop) {
    cudaEventCreate(stop);
    cudaEventRecord(*stop);

    cudaEventSynchronize(*stop);
    cudaEventElapsedTime(&milliseconds, *start, *stop);
    return(milliseconds);
}


void cudaErrorCheck()
{
    cudaError_t error = cudaGetLastError();
    const char* errorName = cudaGetErrorName(error);
    std::string s0(errorName);
    std::cout << ">>>> " << s0 << std::endl;

    const char* errorDescription = cudaGetErrorString(error);
    std::string s1(errorDescription);
    std::cout << ">>>> " << s1 << std::endl;
}



void random_ints(int* a, int b)
{
    int i;
    for (i = 0; i < b; ++i)
        a[i] = rand() % 10;
}

//start of the main program
int main(void)
{
    int *in, *out;
    int *d_in, *d_out;
    int size = N * sizeof(int);
    cudaEvent_t start, stop;

    //Allocating Memory for the device
    cudaMalloc((void**)&d_in, size);
    cudaMalloc((void**)&d_out, size);

    cudaErrorCheck();

    //Allocating Memory for the host and initialzing values for 'in' array
    in = (int*)malloc(size);
    random_ints(in, N);
    out = (int*)malloc(size);
    
    //copying host input memory to device memory
    cudaMemcpy(d_in, in, size, cudaMemcpyHostToDevice);

    cudaErrorCheck();

    //starting the timer to check performance
    start_timer(&start);

    stencil_1d<<<N/block_count, thread_count>>>(d_in, d_out);


    std::cout << "Elapsed time: " << stop_timer(&start, &stop) << " ms" << std::endl;

    cudaErrorCheck();

    cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);

    cudaErrorCheck();

    free(in); free(out);
    cudaFree(d_in); cudaFree(d_out);

}