/**
 * Um exemplo de reducao no OpenMP
 */
#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX 1000

int main() {
    int i;
    int tid;
    float A[1000];
    double media = 0.;
    srand((time(((void *)0))));
    // Regiao paralela para preenchimento do vetor A
    dummyMethod1();
    for (i = 0; i <= 999; i += 1) {
        A[i] = ((rand() % 3) / .275);
    }
    dummyMethod2();
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : media)
    // #pragma rose_outline
    for (i = 0; i <= 999; i += 1) {
        media += A[i];
    }
    printf("Media: %f\n", media / 1000);
    dummyMethod2();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
