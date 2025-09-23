#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void saxpy(int n, float a, float *__restrict__ x, float *__restrict__ y) {
    dummyMethod1();

#pragma omp parallel for firstprivate(n, a)
    // #pragma rose_outline
    for (int i = 0; i <= n - 1; i += 1) {
        y[i] = a * x[i] + y[i];
    }
    for (int i = 0; i <= n - 1; i += 1) {
        printf("y[%d]=%f\n", i, y[i]);
    }
}
int dummyMethod2();

int main(int argc, char *argv[]) {
    /* omp_parfor.c  */
    int n = 1 << 20;
    // 1 milhão de floats
    float *x = (float *)(malloc(n * sizeof(float)));
    float *y = (float *)(malloc(n * sizeof(float)));
    dummyMethod1();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= n - 1; i += 1) {
        x[i] = 2.0f;
        y[i] = 1.0f;
    }
    dummyMethod2();
    saxpy(n, 3.0f, x, y);
    free(x);
    free(y);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
