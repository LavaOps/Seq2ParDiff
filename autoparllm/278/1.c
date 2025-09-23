#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int j;
    int tmp = 0;
    dummyMethod1();

#pragma omp parallel for private(j) reduction(+ : tmp)
    // #pragma rose_outline
    for (j = 0; j <= 999; j += 1) {
        tmp += j;
    }
    printf("%d\n", tmp);
    dummyMethod2();
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
