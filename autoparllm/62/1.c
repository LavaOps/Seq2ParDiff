/**
 * this program is for using the ordered directive
 **/
#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, const char *argv[]) {
    float intermediate = 0;
    float sum;
    int i;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum)                         \
    firstprivate(intermediate)
    // #pragma rose_outline
    for (i = 0; i <= 9; i += 1) {
        {
            sum = intermediate + sum;
        }
    }
    printf("%f", sum);
    dummyMethod2();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
