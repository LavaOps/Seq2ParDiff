#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
const int n = 20;

int main() {
    int a[20];
    int b = 1000;
    dummyMethod1();

#pragma omp parallel for firstprivate(n, b)
    // #pragma rose_outline
    for (int i = 0; i <= n - 1; i += 1) {
        a[i] = b + i;
    }
    dummyMethod2();
    printf("gjggghjjhj");
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
