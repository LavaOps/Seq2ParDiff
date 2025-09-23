#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static long num_steps = 100000;
double step;

double compute_pi() {
    unsigned int i = 0;
    double pi;
    double sum = 0.0;
    step = 1.0 / ((double)num_steps);
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum) firstprivate(num_steps)
    // #pragma rose_outline
    for (i = 0; ((long)i) <= num_steps - 1; i += 1) {
        double x;
        x = (0.5 + ((double)i)) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    dummyMethod2();
    pi = sum * step;
    return pi;
}

int main() {
    printf("pi = %f", (compute_pi()));
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
