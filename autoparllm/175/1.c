/* Parallel Single Precision a*x plus y */
#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    const int N = 1000;
    const double a = .5f;
    double sum = 0.0f;
    double z[1000];
    double x[1000];
    double y[1000];
    int i;
    dummyMethod1();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= N - 1; i += 1) {
        x[i] = (i + 1) * .15;
        y[i] = (i + 1) * .1;
    }
    dummyMethod2();
    dummyMethod1();

#pragma omp parallel for private(i) firstprivate(a)
    // #pragma rose_outline
    for (i = 0; i <= N - 1; i += 1) {
        z[i] = a * x[i] + y[i];
    }
    dummyMethod2();
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum) firstprivate(N)
    // #pragma rose_outline
    for (i = 0; i <= N - 1; i += 1) {
        sum += z[i];
    }
    printf("%f\n", sum);
    dummyMethod2();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
