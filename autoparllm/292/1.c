// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <stdio.h>
#include "omp.h"
#include <omp.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 200

int main() {
    double A[200];
    double C[200];
    double sum0 = 0.0;
    dummyMethod1();

#pragma omp parallel for reduction(+ : sum0)
    // #pragma rose_outline
    for (int i = 0; i <= 199; i += 1) {
        sum0 += A[i] * C[i];
    }
    printf("%f", sum0);
    dummyMethod2();
}
// CHECK: Region is Data Race Free.
// END

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
