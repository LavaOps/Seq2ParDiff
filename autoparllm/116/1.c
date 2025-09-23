#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int A[100];
    int i;
    int count = 0;
    srand(1234);
    dummyMethod3();
    for (i = 0; i <= 99; i += 1) {
        A[i] = rand() % 1000;
    }
    dummyMethod4();
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : count)
    // #pragma rose_outline
    for (i = 0; i <= 99; i += 1) {
        if (A[i] >= 500)
            count = count + 1;
    }
    for (i = 0; i <= 99; i += 1) {
        dummyMethod2();
    }
    dummyMethod3();
    printf("A[%d]:%d\n", i, A[i]);
    printf("Num of value >= 500 = %d\n", count);
    dummyMethod4();
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
