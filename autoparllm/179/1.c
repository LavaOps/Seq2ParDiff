#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv) {
    const size_t N = 10000;
    int a[10000];
    dummyMethod1();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; ((unsigned long)i) <= N - 1; i += 1) {
        a[i] = i;
    }
    dummyMethod2();
    int sum = 0;
    dummyMethod1();

#pragma omp parallel for reduction(+ : sum) firstprivate(N)
    // #pragma rose_outline
    for (int i = 0; ((unsigned long)i) <= N - 1; i += 1) {
        sum += a[i];
    }
    dummyMethod2();
    printf("sum = %d\n", sum);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
