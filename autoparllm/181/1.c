#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int A[] = {(1), (2), (3), (4)};
    int sum = 0;
    int i;
    // dependent for loop
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum)
    // #pragma rose_outline
    for (i = 0; i <= 3; i += 1) {
        sum += A[i];
    }
    dummyMethod2();
    printf("Sum: %d\n", sum);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
