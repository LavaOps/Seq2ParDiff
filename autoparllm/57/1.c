/******************************************************************************
 * FILE: omp_reduction.c
 * DESCRIPTION:
 *   OpenMP Example - Combined Parallel Loop Reduction - C/C++ Version
 *   This example demonstrates a sum reduction within a combined parallel loop
 *   construct.  Notice that default data element scoping is assumed - there
 *   are no clauses specifying shared or private variables.  OpenMP will
 *   automatically make loop index variables private within team threads, and
 *   global variables shared.
 ******************************************************************************/
#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
    int i;
    int n;
    float a[100];
    float b[100];
    float sum;
    /* Some initializations */
    n = 100;
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        a[i] = b[i] = (i * 1.0);
    }
    dummyMethod4();
    sum = 0.0;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum) firstprivate(n)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        sum = sum + a[i] * b[i];
    }
    dummyMethod2();
    printf("Sum = %f\n", sum);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
