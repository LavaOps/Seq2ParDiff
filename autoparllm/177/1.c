#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX 10

int main() {
    // Initialize avg with the identity value for '+'.
    double avg = 0.0;
    double A[10] = {(0), (1), (2), (3), (4), (5), (6), (7), (8), (9)};
    int i;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : avg)
    // #pragma rose_outline
    for (i = 0; i <= 9; i += 1) {
        avg += A[i];
    }
    dummyMethod2();
    avg = avg / 10;
    printf("Avg = %lf", avg);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
