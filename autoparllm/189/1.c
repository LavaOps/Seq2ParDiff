#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

int main() {
    const int finval = 10000;
    double pi_square = 0.0;
#ifdef _OPENMP
#endif
    dummyMethod1();

#pragma omp parallel for reduction(+ : pi_square) firstprivate(finval)
    // #pragma rose_outline
    for (int i = 1; i <= finval; i += 1) {
        double factor = (double)i;
        pi_square += 1.0 / (factor * factor);
    }
#ifdef _OPENMP
#else
    double end_time = 0.0;
#endif
    printf("Pi^2 = %.10f\n", pi_square * 6.0);
#ifdef _OPENMP
#else
    printf("Time taken: %f s\n", end_time);
#endif
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
