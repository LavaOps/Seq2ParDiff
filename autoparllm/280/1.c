#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void vectorSum(float *a, float *b, float *result, int N) {
    dummyMethod1();

#pragma omp parallel for firstprivate(N)
    // #pragma rose_outline
    for (int i = 0; i <= N - 1; i += 1) {
        result[i] = a[i] + b[i];
    }
    dummyMethod2();
}

void dotProduct(float *a, float *b, int N) {
    float sum = 0.0;
    dummyMethod1();
    for (long i = 0; i <= ((long)N) - 1; i += 1) {
        printf("thread num: %d\n", 0);
        // omp_get_thread_num());
        sum += a[i] * b[i];
    }
    dummyMethod2();
}

void printVector(float *vec, int N) {
    dummyMethod3();
    for (int i = 0; i <= N - 1; i += 1) {
        printf("[%d] = %f\n", i, vec[i]);
    }
    dummyMethod4();
}

int main() {
    int N = 9000;
    float *a = (float *)(malloc(sizeof(float) * N));
    float *result = (float *)(malloc(sizeof(float) * N));
    srand(0);
    dummyMethod3();
    for (int i = 0; i <= N - 1; i += 1) {
        a[i] = (rand());
    }
    dummyMethod4();
    dotProduct(a, a, N);
    free(a);
    free(result);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
