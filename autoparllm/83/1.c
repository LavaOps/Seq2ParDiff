// 009_firstprivate clause
#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define n 3

int main() {
    int offset;
    int i;
    int a[3];
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 2; i += 1) {
        a[i] = 1;
    }
    for (i = 0; i <= 2; i += 1) {
        printf("Before : a[%d] = %d\n", i, a[i]);
    }
    dummyMethod4();
    dummyMethod3();
    offset = 10;
    dummyMethod4();
    dummyMethod1();
    for (i = 0; i <= 2; i += 1) {
        if (i == 0 || i == 3 - 1)
            offset = offset + 2;
        a[i] = a[i] + offset;
    }
    dummyMethod2();
    dummyMethod3();
    for (i = 0; i <= 2; i += 1) {
        printf("After: a[%d] = %d\n", i, a[i]);
    }
}
int dummyMethod4();

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
