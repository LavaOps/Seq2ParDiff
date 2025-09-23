// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <stdio.h>
#include "omp.h"
#include <omp.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 20
#define N 20

int main() {
    double data[20][20];
    double mean[20];
    dummyMethod1();

    for (int i = 0; i <= 19; i += 1) {

#pragma omp parallel for
        // #pragma rose_outline
        for (int j = 0; j <= 19; j += 1) {
            data[i][j] -= mean[j];
        }
    }
    for (int i = 0; i <= 19; i += 1) {
        for (int j = 0; j <= 19; j += 1) {
            printf("data[%d][%d]=%f\n", i, j, data[i][j]);
        }
    }
}
int dummyMethod2();
// CHECK: Region is Data Race Free.
// END

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
