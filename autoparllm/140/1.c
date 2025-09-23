/*THIS PROGRAM DOESN'T WORK PROPERLY*/
#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX_ITS 10000

int main() {
    int its_global;
    int i;
    its_global = 0;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : its_global)
    // #pragma rose_outline
    for (i = 0; i <= 9999; i += 1) {
        its_global++;
    }
    dummyMethod2();
    printf("Counter records %i iterations\n", its_global);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
