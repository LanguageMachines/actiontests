#include "config.h"
#ifdef HAVE_OPENMP
#include "omp.h"
#endif
#include "textcat.h"
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

void sub1( int i ){
  double power = pow( i, i );
#pragma omp critical (bla)
  {
    cerr << i << "^" << i << "=" << power << endl;
  }
}

void sub2( int i ){
  double lg = log( i );
#pragma omp critical (bla)
  {
    cerr << " log(" << i << ")=" << lg << endl;
  }
}

int main(){
  cerr << "start" << endl;
#ifdef HAVE_OPENMP
  omp_set_num_threads(8);
  omp_set_nested(1);
  cerr << "OMP: maximum number of threads=" << omp_get_max_threads() << endl;
#else
  cerr << "Too bad. No OpenMP support available! " << endl;
#endif

  auto TC = textcat_Init( "dummy" );
  if ( TC != 0 ){
    cerr << "Surprise!" << endl;
  }
  else {
    cerr << "next step" << endl;
  }
#pragma omp parallel for
  for ( int i=0; i < 30; ++i ){
#pragma omp parallel sections
    {
#pragma omp section
      {
	sub1( i );
      }
#pragma omp section
      {
	sub2( i );
      }
    }
  }
}
