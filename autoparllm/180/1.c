#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static long num_steps = 10000000;
double step;

int main() {
    int i;
    double pi;
    double sum = 0.0;
    step = 1.0 / ((double)num_steps);
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum) firstprivate(num_steps)
    // #pragma rose_outline
    for (i = 0; ((long)i) <= num_steps - 1; i += 1) {
        double x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    dummyMethod2();
    pi = step * sum;
    printf("pi = %e\n", pi);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
