#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, const char *argv[]) {
    long sum = 0;
    dummyMethod1();

#pragma omp parallel for reduction(+ : sum)
    // #pragma rose_outline
    for (long i = 1; i <= ((long)1000000001) - 1; i += 1) {
        sum += i;
    }
    dummyMethod2();
    printf("Sum of 1 to 1000000000: %ld\n", sum);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
