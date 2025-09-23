#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for timing purposes.
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
// With OpenMP:

void mxvWithOpenMP(int m, int n, double *a, double *b, double *c) {
    int i;
    int j;
    dummyMethod1();
    for (i = 0; i <= m - 1; i += 1) {
        // a[i] = 0.0;
        for (j = 0; j <= n - 1; j += 1) {
            a[i] += b[i * n + j] * c[j];
            // End of omp parallel for statement.
        }
    }
    dummyMethod2();
}
// Without OpenMP:

void mxvWithoutOpenMP(int m, int n, double *a, double *b, double *c) {
    dummyMethod3();
    for (int i = 0; i <= m - 1; i += 1) {
        // a[i] = 0.0;
        for (int j = 0; j <= n - 1; j += 1) {
            a[i] += b[i * n + j] * c[j];
        }
    }
    dummyMethod4();
}

int main(int argc, char *argv[]) {
    double *a;
    double *b;
    double *c;
    int m;
    int n;
    // printf("Please give m and n: ");
    // scanf("%d %d", &m, &n);
    m = n = 10000;
    // Reserve memory for arrays.
    if ((a = ((double *)(malloc(m * sizeof(double))))) == ((void *)0))
        perror("memory allocation for a");
    if ((b = ((double *)(malloc((m * n) * sizeof(double))))) == ((void *)0))
        perror("memory allocation for b");
    if ((c = ((double *)(malloc(n * sizeof(double))))) == ((void *)0))
        perror("memory allocation for c");
    // Initalize arrays.
    printf("Initializing matrix B and vector c\n");
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int j = 0; j <= n - 1; j += 1) {
        c[j] = 2.0;
    }
    dummyMethod4();
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= m - 1; i += 1) {

#pragma omp parallel for
        // #pragma rose_outline
        for (int j = 0; j <= n - 1; j += 1) {
            b[i * n + j] = i;
        }
    }
    dummyMethod4();
    // Conduct comparison.
    printf("Executing mxv function without OpenMP for m = %d n = %d\n", m, n);
    clock_t tic = clock();
    // start timer.
    mxvWithoutOpenMP(m, n, a, b, c);
    clock_t toc = clock();
    // terminate timer.
    printf("Elapsed: %f seconds\n",
           ((double)(toc - tic)) / ((__clock_t)1000000));
    printf("Executing mxv2 function with OpenMP for m = %d n = %d\n", m, n);
    tic = clock();
    // start timer.
    mxvWithOpenMP(m, n, a, b, c);
    toc = clock();
    // terminate timer.
    printf("Elapsed: %f seconds\n",
           ((double)(toc - tic)) / ((__clock_t)1000000));
    // Exit
    free(a);
    free(b);
    free(c);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
