/* --- File matrix_sum_omp.c --- */
#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv) {
    struct timespec ts_start;
    struct timespec ts_end;
    int size = 1e4;
    int **a;
    int *c;
    int i;
    int j;
    float time_total;
    /* Allocate memory */
    c = (malloc(size * sizeof(int)));
    a = ((int **)(malloc(size * sizeof(int *))));
    dummyMethod3();
    for (i = 0; i <= size - 1; i += 1) {
        a[i] = (malloc(size * sizeof(int)));
    }
    /* Set all matrix elements to 1 */
    dummyMethod4();
    dummyMethod3();

    for (i = 0; i <= size - 1; i += 1) {

#pragma omp parallel for private(j)
        // #pragma rose_outline
        for (j = 0; j <= size - 1; j += 1) {
            a[i][j] = 1;
        }
    }
    dummyMethod4();
    /* Zero the accumulator */
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= size - 1; i += 1) {
        c[i] = 0;
    }
    dummyMethod4();
    clock_gettime(1, &ts_start);
    dummyMethod1();
    /* Each thread sums one column */

#pragma omp parallel for private(i, j)
    // #pragma rose_outline
    for (i = 0; i <= size - 1; i += 1) {
        for (j = 0; j <= size - 1; j += 1) {
            c[i] += a[i][j];
        }
    }
    dummyMethod2();
    int total = 0;
    /* Add sums of all columns together */
    dummyMethod3();

#pragma omp parallel for private(i) reduction(+ : total) firstprivate(size)
    // #pragma rose_outline
    for (i = 0; i <= size - 1; i += 1) {
        total += c[i];
    }
    dummyMethod4();
    clock_gettime(1, &ts_end);
    time_total = ((ts_end.tv_sec - ts_start.tv_sec) * 1e9 +
                  (ts_end.tv_nsec - ts_start.tv_nsec));
    printf("Total is %d, time is %f ms\n", total, time_total / 1e6);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
