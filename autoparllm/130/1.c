#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 5000000

int main() {
    double *B;
    double *C;
    B = ((double *)(malloc(sizeof(double) * 5000000)));
    C = ((double *)(malloc(sizeof(double) * 5000000)));
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= 4999999; i += 1) {
        B[i] = 1.0;
        C[i] = 1.0;
    }
    dummyMethod4();
    double sum = 0;
    dummyMethod1();

#pragma omp parallel for reduction(+ : sum)
    // #pragma rose_outline
    for (int i = 0; i <= 4999999; i += 1) {
        sum += B[i] * C[i];
    }
    printf("SUM = %f\n", sum);
    if (sum != 5000000) {
        dummyMethod2();
        printf("Failed!\n");
        return -1;
    } else {
        printf("SUCCESS!\n");
    }
    free(B);
    free(C);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
