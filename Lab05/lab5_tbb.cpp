/*
*	Harjot Mangat 
*	EECS 245 - Parallel Computing
*	Lab 05 - Parallel_for on a serial program
*/


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
using namespace std;

typedef complex<double> dcmplx;


// generates a random complex number on the complex unit circle
dcmplx random_dcmplx ( void )
{
   int r = rand();
   double d = ((double) r)/RAND_MAX;
   double e = 2*M_PI*d;
   dcmplx c(cos(e),sin(e));
   return c;
}

// writes the array of n doubles in x
void write_numbers ( int n, dcmplx *x )
{
   for(int i=0; i<n; i++)
      cout << scientific << setprecision(4)
           << "x[" << i << "] = ( " << x[i].real()
           << " , " << x[i].imag() << ")\n";
}

// for arrays x and y of length n, on return y[i] equals x[i]**d
void compute_powers ( int n, dcmplx *x, dcmplx *y, int d )
{
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n, 1),
        [=](const tbb::blocked_range<size_t>& z) -> void {
            for (size_t i = z.begin(); i != z.end(); i++)// int i = 0; i < n; i++)  y[i] = pow(x[i],d); pow is too efficient
            {
                dcmplx r(1.0, 0.0);
                for (int j = 0; j < d; j++) r = r * x[i];
                y[i] = r;
            }
        });
}


int main(int argc, char* argv[])
{

    int v = 1;    // verbose if > 0
    if (argc > 3) v = atoi(argv[3]);
    int dim;      // get the dimension
    if (argc > 1)
        dim = atoi(argv[1]);
    else
    {
        cout << "how many numbers ? ";
        cin >> dim;
    }
    tbb::tick_count t0 = tbb::tick_count::now();
    // fix the seed for comparisons
    srand(20120203); //srand(time(0));

    //allocate r
    dcmplx* r = new dcmplx[dim];
    tbb::parallel_for(tbb::blocked_range<size_t>(0, dim, 1),
        [=](const tbb::blocked_range<size_t>& h) -> void {
        for (size_t i = h.begin(); i != h.end(); i++)   //int i = 0; i < dim; i++)
            r[i] = random_dcmplx();
        });
   if(v > 0) write_numbers(dim,r);
   tbb::tick_count t1 = tbb::tick_count::now();
   printf("random_dcmplx and write_numbers took %g seconds\n", (t1 - t0).seconds());
   int deg;      // get the degree
   if(argc > 1)
      deg = atoi(argv[2]);
   else
   {
      cout << "give the power : ";
      cin >> deg;
   }

   tbb::tick_count t2 = tbb::tick_count::now();

   //allocate s
   dcmplx* s = new dcmplx[dim];
   compute_powers(dim,r,s,deg);
   if(v > 0) write_numbers(dim,s);

   tbb::tick_count t3 = tbb::tick_count::now();
   printf("compute_powers and write_numbers took %g seconds\n", (t3 - t2).seconds());
   
   printf("total compuation time taken was %g seconds\n", ((t3 - t2) + (t1 - t0)).seconds());

   delete[] r;
   delete[] s;
   return 0;
}