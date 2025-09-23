// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <stdio.h>
#include "omp.h"
#include <omp.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 200
#define N 200

int main() {
    double A[200];
    double B[200][200];
    double C[200];
    double sum = 0.0;
    dummyMethod1();
    for (int i = 0; i <= 199; i += 1) {

#pragma omp parallel for reduction(+ : sum)
        // #pragma rose_outline
        for (int j = 0; j <= 199; j += 1) {
            sum += B[i][j] * C[j];
        }
        A[i] = sum;
        sum = 0.0;
    }
    for (int i = 0; i <= 199; i += 1) {
        printf("A[%d]=%f\n", i, A[i]);
    }
    dummyMethod2();
}
// CHECK: Region is Data Race Free.
// END

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
