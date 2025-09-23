#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int A[100];
    int B[100];
    int i;
    srand(1234);
    dummyMethod3();
    for (i = 0; i <= 99; i += 1) {
        A[i] = rand() % 1000;
    }
    dummyMethod4();
    dummyMethod1();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 99; i += 1) {
        B[i] = A[i] * 10;
    }
    for (i = 0; i <= 99; i += 1) {
        dummyMethod2();
    }
    dummyMethod3();
    printf("[%d]: A = %d | B = %d\n", i, A[i], B[i]);
}
int dummyMethod4();

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
