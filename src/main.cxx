#include "omp.h"
#include "textcat.h"
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

int main(){
  cerr << "start" << endl;
  cerr << "OMP: num of threads=" << omp_get_num_threads() << endl;
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
