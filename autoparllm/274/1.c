#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int i;
    int n;
    int chunk;
    float a[100];
    float result;
    n = 100;
    chunk = 10;
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        a[i] = (i * 1.0);
    }
    result = 0.0;
    dummyMethod4();
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : result)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        result = result + a[i];
    }
    printf("Average = %f\n", (result / ((float)n)));
    dummyMethod2();
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
