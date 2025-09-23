#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, const char *argv[]) {
    int i;
    int n = 1024;
    float a = 2.0f;
    float *x = (float *)(malloc(n * sizeof(float)));
    float *y = (float *)(malloc(n * sizeof(float)));
    {
        dummyMethod1();

#pragma omp parallel for private(i) firstprivate(n, a)
        // #pragma rose_outline
        for (i = 0; i <= n - 1; i += 1) {
            y[i] = a * x[i] + y[i];
        }
        for (i = 0; i <= n - 1; i += 1) {
            printf("y[%d]=%f\n", i, y[i]);
        }
        dummyMethod2();
    }
    free(x);
    free(y);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
