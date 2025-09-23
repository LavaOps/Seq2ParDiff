#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1024

void main() {
    int n = 1024;
    int a = 2;
    int i;
    int begin;
    int *x;
    int *y;
    int *z;
    x = ((int *)(malloc(n * sizeof(int))));
    y = ((int *)(malloc(n * sizeof(int))));
    z = ((int *)(malloc(n * sizeof(int))));
    dummyMethod3();
    for (i = 0; i != n; i += 1) {
        x[i] = i;
        y[i] = 2 * i;
        z[i] = 0.0;
    }
    dummyMethod4();
    // for (i = 0; i < n; i++)
    //     x[i] = i;
    dummyMethod1();

#pragma omp parallel for private(i) firstprivate(a)
    // #pragma rose_outline
    for (i = 0; i <= 1023; i += 1) {
        z[i] = a * x[i] + y[i];
    }
    printf("Checking Result...\n");
    dummyMethod2();
    dummyMethod3();
    for (i = 0; i <= n - 1; i += 1) {
        if (a * x[i] + y[i] != z[i]) {
            printf("Result is wrong at %d!!!\n", i);
            break;
        }
    }
    printf("Result checked!!!\n");
    dummyMethod4();
    return;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
