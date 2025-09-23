// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <stdio.h>
#include "omp.h"
#include <omp.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20

int main() {
    int A[20][20][20];
    dummyMethod1();
    for (int i = 1; i <= 19; i += 1) {

        for (int j = 1; j <= 19; j += 1) {

#pragma omp parallel for
            // #pragma rose_outline
            for (int k = 1; k <= 19; k += 1) {
                A[i][j][k] = A[i - 1][j][k];
            }
        }
    }
    for (int i = 0; i <= 19; i += 1) {
        for (int j = 0; j <= 19; j += 1) {
            for (int k = 0; k <= 19; k += 1) {
                printf("A[%d][%d][%d]=%d\n", i, j, k, A[i][j][k]);
            }
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
