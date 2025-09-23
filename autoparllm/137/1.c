#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100000
#define TOL 0.0000001
//
//  This is a simple program to add two vectors
//  and verify the results.
//
//  History: Written by Tim Mattson, November 2017
//

int main() {
    float a[100000];
    float b[100000];
    float c[100000];
    float res[100000];
    int err = 0;
    // fill the arrays
    dummyMethod1();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= 99999; i += 1) {
        a[i] = ((float)i);
        b[i] = (2.0 * ((float)i));
        c[i] = 0.0;
        res[i] = (i + 2 * i);
    }
    dummyMethod2();
    // add two vectors
    dummyMethod1();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= 99999; i += 1) {
        c[i] = a[i] + b[i];
    }
    dummyMethod2();
    // test results
    dummyMethod1();

#pragma omp parallel for reduction(+ : err)
    // #pragma rose_outline
    for (int i = 0; i <= 99999; i += 1) {
        float val = c[i] - res[i];
        val = val * val;
        if (val > 0.0000001)
            err++;
    }
    dummyMethod2();
    printf(" vectors added with %d errors\n", err);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
