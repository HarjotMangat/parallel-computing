========================================
* Harjot Mangat                        *
* EECS 245 - Parallel Computing        *
* Lab 04                               *
========================================


**************************
*****N_Queens_sol.ccp*****
**************************
This program uses Cilk+ to find a solution to the N-Queens problem. This program uses the following include definitions:

	'iostream'
	'stdbool.h'
	'stdio.h'
	'cilk/cilk.h'	The include might be different for your system.

I had great difficulty trying to get Cilk+ working. I ended up using the Intel oneAPI DPC++/C++ Compiler & Intel C++ Compiler Classic. As mentioned, the include for the cilk header function might be different for your system.

I was not able to implement the ability for the user to directly control the number of queens from console or input.
The value that controls the number of queens is #define N, in the code.
