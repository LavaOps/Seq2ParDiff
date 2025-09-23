#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void randInit(int array[], const int n) {
    srand((time(((void *)0))));
    dummyMethod3();
    for (int i = 0; i <= n - 1; i += 1) {
        array[i] = rand() % 100;
    }
}
int dummyMethod4();

double mean(int array[], const int n) {
    double sum = 0;
    dummyMethod1();

#pragma omp parallel for reduction(+ : sum)
    // #pragma rose_outline
    for (int i = 0; i <= n - 1; i += 1) {
        sum += array[i];
    }
    return ((double)sum) / n;
    dummyMethod2();
}

int main() {
    const int N = 10;
    int a[10];
    int b[10];
    randInit(a, N);
    randInit(b, N);
    printf("a mean == %f; b mean == %f\n", (mean(a, N)), (mean(b, N)));
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
