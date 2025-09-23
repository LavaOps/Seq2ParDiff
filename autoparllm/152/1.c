#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    dummyMethod1();
    for (int num = 0; num <= 9999; num += 1) {
        int counter = 0;

#pragma omp parallel for reduction(+ : counter)
        // #pragma rose_outline
        for (int i = 1; i <= num; i += 1) {
            if (num % i == 0)
                counter++;
        }
        if (counter == 2)
            printf("Prime %d\n", num);
    }
    dummyMethod2();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
