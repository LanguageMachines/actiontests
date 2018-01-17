#include "config.h"
#ifdef HAVE_OPENMP
#include "omp.h"
#endif
#include <cmath>
#include <unistd.h> // sleep()
#include <wait.h> // wait()
#include <string>
#include <iostream>

using namespace std;

void suba(){
#pragma omp parallel num_threads(2)
  {
    int r = 1 + rand() % 3;
    sleep( r );
#pragma omp critical (bla)
    cerr << "sub_a(" << r << ")" << endl; // output twice
  }
#pragma omp critical (bla)
  cerr << "sub_a ended" << endl; // output once
}

void subb(){
#pragma omp parallel num_threads(2)
  {
    int r = 1 + rand() % 4;
    sleep( r );
#pragma omp critical (bla)
    cerr << "sub_b(" << r << ")" << endl; // output twice
  }
#pragma omp critical (bla)
  cerr << "sub_b ended" << endl; // output once
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

  suba( );
#if defined(__clang__)
  cerr << "Clang detected, go on!" << endl;
#elif defined (__GNUC__)
  cerr << "GCC detected, so bail out before fork" << endl;
  return EXIT_SUCCESS;
#endif
  int p = fork();
  if ( !p ) {
    subb( );
    exit(EXIT_SUCCESS);
  }
  wait(NULL);
  return EXIT_SUCCESS;
}
