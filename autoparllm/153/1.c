#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv) {
    const long N = 1000000;
    int i;
    int a[1000000];
    dummyMethod1();

#pragma omp parallel for private(i) firstprivate(N)
    // #pragma rose_outline
    for (i = 0; ((long)i) <= N - 1; i += 1) {
        a[i] = 2 * a[i];
    }
    for (i = 0; ((long)i) <= N - 1; i += 1) {
        printf("a[%ld]=%d\n", i, a[i]);
    }
    return 0;
    dummyMethod2();
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
