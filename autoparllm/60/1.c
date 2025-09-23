#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 1000
#define INT_MAX 999
// Ejecutado con 8 hilos

int main() {
    int A[1000];
    int i;
    int result = 999;
    // Preguntar a Arturo pq al paralelizar este bucle tarda más que si lo dejas
    // sin paralelizar
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 999; i += 1) {
        A[i] = i;
    }
    dummyMethod4();
    /* M ́ınimo de valores en un array */
    dummyMethod1();

    for (i = 0; i <= 999; i += 1) {
        if (A[i] < result)
            result = A[i];
    }
    dummyMethod2();
    printf("Suma %d\n", result);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
