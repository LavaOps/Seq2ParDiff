#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int i;
    int res = 0;
    int *a = (int *)(calloc(10000000, sizeof(int)));
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : res)
    // #pragma rose_outline
    for (i = 0; i <= 9999999; i += 1) {
        res = res + a[i];
    }
    dummyMethod2();
    printf("result is %d", res);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
