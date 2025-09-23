/*
Create a program that computes a simple matrix vector multiplication
b=Ax, either in fortran or C/C++. Use OpenMP directives to make
it run in parallel.
This is the parallel version.
*/
#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    float A[2][2] = {
        /* Need explicit braces: is this where we insert the class name? */ {
            (1), (2)},
        /* Need explicit braces: is this where we insert the class name? */ {
            (3), (4)}};
    float b[] = {(8), (10)};
    float c[2];
    int i;
    int j;
    // computes A*b
    dummyMethod1();

#pragma omp parallel for private(i, j)
    // #pragma rose_outline
    for (i = 0; i <= 1; i += 1) {
        c[i] = 0;
        for (j = 0; j <= 1; j += 1) {
            c[i] = c[i] + A[i][j] * b[j];
        }
    }
    dummyMethod2();
    // prints result
    dummyMethod3();
    for (i = 0; i <= 1; i += 1) {
        printf("c[%i]=%f \n", i, c[i]);
    }
    dummyMethod4();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
