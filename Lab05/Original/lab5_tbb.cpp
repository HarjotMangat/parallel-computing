#include <iostream>
#include <iomanip>
#include <complex>
#include <cstdlib>
#include <cmath>
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
   for(int i=0; i < n; i++) // y[i] = pow(x[i],d); pow is too efficient
   {
      dcmplx r(1.0,0.0);
      for(int j=0; j < d; j++) r = r*x[i];
      y[i] = r;
   }
}


int main ( int argc, char *argv[] )
{
   int v = 1;    // verbose if > 0
   if(argc > 3) v = atoi(argv[3]);
   int dim;      // get the dimension
   if(argc > 1)
      dim = atoi(argv[1]);
   else
   {
      cout << "how many numbers ? ";
      cin >> dim;
   }
   // fix the seed for comparisons
   srand(20120203); //srand(time(0));
   dcmplx r[dim];
   for(int i=0; i<dim; i++)
      r[i] = random_dcmplx();
   if(v > 0) write_numbers(dim,r);
   int deg;      // get the degree
   if(argc > 1)
      deg = atoi(argv[2]);
   else
   {
      cout << "give the power : ";
      cin >> deg;
   }
   dcmplx s[dim];
   compute_powers(dim,r,s,deg);
   if(v > 0) write_numbers(dim,s);

   return 0;
}