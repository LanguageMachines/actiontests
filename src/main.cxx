#include "config.h"
#ifdef HAVE_OPENMP
#include "omp.h"
#endif
#include "textcat.h"
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

int main(){
  cerr << "start" << endl;
#ifdef HAVE_OPENMP
  omp_set_num_threads(8);
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
#pragma omp critical
    {
      cerr << "I=" << i << " i^i=" << pow(i,i) << endl;
    }
  }

}
