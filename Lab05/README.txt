========================================
* Harjot Mangat                        *
* EECS 245 - Parallel Computing        *
* Lab 05                               *
========================================


**********************
*****lab5_tbb.ccp*****
**********************
This program uses TBB to parallelize the serial code given in the original Lab5_tbb.cpp. This program uses the following include definitions:

	#include <iostream>
	#include <iomanip>
	#include <complex>
	#include <cstdlib>
	#include <cmath>
	#define _USE_MATH_DEFINES
	#include <math.h>
	#include <tbb/blocked_range.h>
	#include <tbb/parallel_for.h>
	#include <tbb/tick_count.h>

I used the Intel oneAPI DPC++/C++ Compiler & Intel C++ Compiler Classic.
The TBB includes might be different for your system.
