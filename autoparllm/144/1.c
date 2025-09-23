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
    int size = 1e8;
    int multiplier = 2;
    int *a;
    int *c;
    int i;
    float time_total;
    /* Allocate memory for arrays */
    a = (malloc(size * sizeof(int)));
    c = (malloc(size * sizeof(int)));
    /* Get start time */
    clock_gettime(1, &ts_start);
    /* Multiply array a by multiplier */
    dummyMethod1();

#pragma omp parallel for private(i) firstprivate(size, multiplier)
    // #pragma rose_outline
    for (i = 0; i <= size - 1; i += 1) {
        c[i] = multiplier * a[i];
    }
    dummyMethod2();
    /* Get end time */
    clock_gettime(1, &ts_end);
    time_total = ((ts_end.tv_sec - ts_start.tv_sec) * 1e9 +
                  (ts_end.tv_nsec - ts_start.tv_nsec));
    printf("Total time is %f ms\n", time_total / 1e6);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
