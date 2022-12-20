========================================
* Harjot Mangat                        *
* EECS 245 - Parallel Computing        *
* Lab 01                               *
========================================


*****************
****kernel.cu****
*****************
The kernel.cu file is the implementation for 2.1 of Lab01. It can be compiled with CUDA 11.6 or any version of CUDA with the following include definitions:
	'cuda_runtime.h'
	'device_launch_parameters.h'

Can be compiled with nvcc

******************
****Texture.cu****
******************
I was unable to get this file to compile or work. It should be the theoretical implementation of 2.2 of Lab01. It should be run with a version of CUDA < 11.7. It has the following include definitions:
	'cuda_runtime.h'
	'cuda_runtime_api.h'
	'device_launch_paramters.h'
	'cuda_texture_types.h'
	'texture_types.h'
	'cuda.h'

Can be compiled with nvcc

*******************
****Constant.cu****
*******************
The Constant.cu file implements constant memory for 2.3 of Lab01. It can be compiled with CUDA 11.6 or any version of CUDA with the following include definitions:
	'cuda_runtime.h'
	'device_launch_paramters.h'
	'device_functions.h'

Can be compiled with nvcc

**************************
****CUDA_Matrix_Mul.cu****
**************************
This was originally a CUDA sample program by NVidia. I adjusted and trimmed down the project to fit our requirement for 3 of Lab01. It should run with CUDA 11.6 or and version of CUDA with the following includde definitions:
	'cuda_runtime.h'
	'cuda_profiler_api.h'
	'cuda_device_runtime_api.h'
	'device_launch_parameters.h'
	'device_functions.h'
	'cuda_pipeline_helpers.h'

Can be compiled with nvcc