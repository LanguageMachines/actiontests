#include "config.h"
#ifdef HAVE_OPENMP
#include "omp.h"
#endif
#ifdef HAVE_TEXTCAT
  #ifdef HAVE_OLD_TEXTCAT
    #ifdef __cplusplus
extern "C" {
    #endif
  #endif
#include "textcat.h"
  #ifdef HAVE_OLD_TEXTCAT
    #ifdef __cplusplus
}
   #endif
  #endif
#endif
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
  cerr << endl << "start main()" << endl;
#ifdef HAVE_OPENMP
  omp_set_num_threads(8);
  omp_set_nested(1);
  cerr << "OMP: maximum number of threads=" << omp_get_max_threads() << endl;
#else
  cerr << "Too bad. No OpenMP support available! " << endl;
#endif

#ifdef HAVE_TEXTCAT
  string textcat_cfg = string(SYSCONF_PATH) + "/travistest/textcat.cfg";
  auto TC = textcat_Init( textcat_cfg.c_str() );
  if ( TC != 0 ){
    cerr << "Textcat initialized!" << endl;
    string in = "Een korte nederlandse zin.";
    char *res = textcat_Classify( TC, in.c_str(), in.size() );
    cerr << "classify==> " << res << endl;
  }
  else {
    cerr << " textcat init failed" << endl;
    return EXIT_FAILURE;
  }
#else
  cerr << "NO TEXTCAT SUPPORT!?" << endl;
#endif
#pragma omp parallel for
  for ( int i=0; i < 20; ++i ){
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
  cerr << "end main()" << endl;
  return EXIT_SUCCESS;
}
