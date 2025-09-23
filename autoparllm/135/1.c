#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 3
int A[3][3];
int B[3][3];

int main() {
    int i;
    int j;
    int k;
    for (i = 0; i <= 2; i += 1) {
        dummyMethod3();
    }

#pragma omp parallel for private(j) firstprivate(i)
    // #pragma rose_outline
    for (j = 0; j <= 2; j += 1) {
        A[i][j] = i;
    }
    dummyMethod4();
    dummyMethod3();
    for (i = 0; i <= 2; i += 1) {
        for (j = 0; j <= 2; j += 1) {
            B[j][i] = A[i][j];
        }
    }
    dummyMethod4();
    for (i = 0; i <= 2; i += 1) {
        dummyMethod1();
    }
    {
        for (j = 0; j <= 2; j += 1) {
            printf("%d\t", B[i][j]);
        }
        dummyMethod2();
        printf("\n");
    }
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
