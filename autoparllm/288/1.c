// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
// Taken from ompVerify, Sec 4.3
#include <stdio.h>
#include "omp.h"
#include <omp.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20

int main() {
    int i;
    int j;
    int A[20];
    int a[20][20];
    int B[20][20];
    dummyMethod1();
    for (i = 0; i <= 19; i += 1) {

#pragma omp parallel for private(j)
        // #pragma rose_outline
        for (j = 0; j <= i - 1; j += 1) {
            A[j] = a[i][j];
            B[i][j] = A[j];
        }
    }
    for (i = 0; i <= 19; i += 1) {
        for (j = 0; j <= i-1; j += 1) {
            printf("B[%d][%d]=%d\n", i, j, B[i][j]);
        }
    }
}
int dummyMethod2();
// CHECK: Data Race detected
// END

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
