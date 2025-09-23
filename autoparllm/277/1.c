#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1024

int main() {
    float *a;
    float *b;
    float *c;
    int i;
    a = ((float *)(malloc(1024 * sizeof(float))));
    b = ((float *)(malloc(1024 * sizeof(float))));
    c = ((float *)(malloc(1024 * sizeof(float))));
    // initialize a, b, and c (code not shown)
    dummyMethod1();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 1023; i += 1) {
        c[i] += a[i] * b[i];
    }
    for (i = 0; i <= 1023; i += 1) {
        printf("c[%d]=%f\n", i, c[i]);
    }
}
int dummyMethod2();

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
