#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int sum = 0;
    int N = 10;
    int i;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum) firstprivate(N)
    // #pragma rose_outline
    for (i = 0; i <= N - 1; i += 1) {
        sum++;
    }
    dummyMethod2();
    printf("%d\n", sum);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
