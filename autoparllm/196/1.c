#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif
int counter = 0;

int main() {
    int i;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : counter)
    // #pragma rose_outline
    for (i = 0; i <= 99; i += 1) {
        counter++;
    }
    dummyMethod2();
    printf("counter=%d\n", counter);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
