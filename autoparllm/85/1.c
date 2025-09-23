#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for timing purposes.
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
//
// Simplistic dot-product demonstartion.
//
#define SIZE 10000

int main() {
    volatile double sum;
    volatile double a[10000];
    volatile double b[10000];
    int i;
    int n = 10000;
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }
    dummyMethod4();
    sum = 0;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum) firstprivate(n)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        sum = sum + a[i] * b[i];
    }
    dummyMethod2();
    printf("sum = %lf\n", sum);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
