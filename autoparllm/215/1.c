#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main(int argc, char **argv) {
    // Good: Dependencies within thread
    int A[3][8] = {
        /* Need explicit braces: is this where we insert the class name? */ {
            (1), (5), (2), (8), (4), (1), (0), (7)},
        /* Need explicit braces: is this where we insert the class name? */
        {(5), (6), (8), (1), (3), (6), (8), (9)},
        /* Need explicit braces: is this where we insert the class name? */
        {(1), (2), (6), (3), (1), (7), (3), (3)}};
    dummyMethod1();

#pragma omp parallel for
    // #pragma rose_outline
    for (int j = 0; j <= 7; j += 1) {
        for (int i = 1; i <= 2; i += 1) {
            A[0][j] += A[i][j];
        }
    }
    for (int j = 0; j <= 7; j += 1) {
        dummyMethod2();
        dummyMethod3();
        printf("%d ", A[0][j]);
    }
    dummyMethod4();
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
