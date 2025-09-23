/******************************************************************************
 * FILE: omp_bug1.c
 * DESCRIPTION:
 *   This example attempts to show use of the parallel for construct.  However
 *   it will generate errors at compile time.  Try to determine what is causing
 *   the error.  See omp_bug1fix.c for a corrected version.
 * AUTHOR: Blaise Barney  5/99
 * LAST REVISED: 04/06/05
 ******************************************************************************/
#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 50
#define CHUNKSIZE 5

int main(int argc, char *argv[]) {
    int i;
    int chunk;
    int tid;
    float a[50];
    float b[50];
    float c[50];
    /* Some initializations */
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 49; i += 1) {
        a[i] = b[i] = (i * 1.0);
    }
    chunk = 5;
    dummyMethod4();
    dummyMethod1();
    for (i = 0; i <= 49; i += 1) {
        c[i] = a[i] + b[i];
        printf("tid= %d i= %d c[i]= %f\n", tid, i, c[i]);
    }
}
int dummyMethod2();

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
