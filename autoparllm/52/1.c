#include "omp.h"
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX_TERMS 1e9

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./pi thread count");
        return 0;
    }
    int thread_count = atoi(argv[1]);
    double result = 0;
    struct timeval tval_before;
    struct timeval tval_after;
    struct timeval tval_result;
    gettimeofday(&tval_before, (void *)0);
    dummyMethod1();

#pragma omp parallel for reduction(+ : result)
    // #pragma rose_outline
    for (int i = 0; ((long)i) <= ((long)1e9) - 1; i += 1) {
        result += 4.0 * ((i % 2 == 0 ? 1 : -1)) / (2.0 * i + 1);
    }
    dummyMethod2();
    gettimeofday(&tval_after, (void *)0);
    do {
        (&tval_result)->tv_sec = (&tval_after)->tv_sec - (&tval_before)->tv_sec;
        (&tval_result)->tv_usec =
            (&tval_after)->tv_usec - (&tval_before)->tv_usec;
        if ((&tval_result)->tv_usec < 0) {
            --(&tval_result)->tv_sec;
            (&tval_result)->tv_usec += 1000000;
        }
    } while (0);
    printf("Time elapsed: %ld.%06ld\n", (long)tval_result.tv_sec,
           (long)tval_result.tv_usec);
    printf("\npi: %2.12f \n", result);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
