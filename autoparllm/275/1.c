#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static long num_steps = 100000000;
double step;

int main() {
    int i;
    double x;
    double pi;
    double sum = 0.0;
    step = 1.0f / ((double)num_steps);
    dummyMethod1();

#pragma omp parallel for private(x, i) reduction(+ : sum)                      \
    firstprivate(num_steps)
    // #pragma rose_outline
    for (i = 0; ((long)i) <= num_steps - 1; i += 1) {
        x = (i + 0.5f) * step;
        sum += 4.0f / (1.0f + x * x);
    }
    dummyMethod2();
    pi = step * sum;
    printf("pi=%f\n", pi);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
