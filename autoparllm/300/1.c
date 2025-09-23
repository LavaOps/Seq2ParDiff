// gcc -fopenmp piParallel.c
//./a.out
#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
long num_steps = 1000000;
// Program To Calculate Pi value

int main() {
    int i;
    double sum = 0.0;
    double x;
    double pi;
    double step = ((double)1.0) / num_steps;
    {
        double x;
        dummyMethod1();

#pragma omp parallel for private(x, i) reduction(+ : sum)                      \
    firstprivate(num_steps)
        // #pragma rose_outline
        for (i = 0; ((long)i) <= num_steps - 1; i += 1) {
            x = ((double)(i + 0.5)) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }
        dummyMethod2();
        pi = step * sum;
    }
    printf("%f\n", pi);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
