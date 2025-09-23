/**
 * gesummv.c: This file was adapted from PolyBench/GPU 1.0 test
 * suite to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *           Luís Felipe Mattos <ra107822@students.ic.unicamp.br>
 */
#include "omp.h"
#include <omp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// polybenchUtilFuncts.h
// Scott Grauer-Gray (sgrauerg@gmail.com)
// Functions used across hmpp codes
#ifndef POLYBENCH_UTIL_FUNCTS_H
#define POLYBENCH_UTIL_FUNCTS_H
// define a small float value
#define SMALL_FLOAT_VAL 0.00000001f

double rtclock() {
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday(&Tp, (&Tzp));
    if (stat != 0)
        printf("Error return from gettimeofday: %d", stat);
    return Tp.tv_sec + Tp.tv_usec * 1.0e-6;
}

float absVal(float a) {
    if (a < 0) {
        return a * (-1);
    } else {
        return a;
    }
}

float percentDiff(double val1, double val2) {
    if ((absVal(val1)) < 0.01 && (absVal(val2)) < 0.01) {
        return 0.0f;
    } else {
        return 100.0f *
               absVal(absVal((val1 - val2)) / absVal((val1 + 0.00000001f)));
    }
}
#endif // POLYBENCH_UTIL_FUNCTS_H
int main();
// define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.05
#define GPU_DEVICE 1
#ifdef _DEBUG_1
/* Problem size */
#define N 32768
#elif _DEBUG_2
/* Problem size */
#define N 16384
#else
/* Problem size */
#define N 8192
#endif
/* Declared constant values for ALPHA and BETA (same as values in PolyBench 2.0)
 */
#define ALPHA 43532.0f
#define BETA 12313.0f
/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void gesummv(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *x, DATA_TYPE *y,
             DATA_TYPE *tmp) {
    int i;
    int j;
    dummyMethod3();
    for (i = 0; i <= 8191; i += 1) {
        tmp[i] = 0;
        y[i] = 0;
        for (j = 0; j <= 8191; j += 1) {
            tmp[i] = A[i * 8192 + j] * x[j] + tmp[i];
            y[i] = B[i * 8192 + j] * x[j] + y[i];
        }
        y[i] = 43532.0f * tmp[i] + 12313.0f * y[i];
    }
    dummyMethod4();
}

void GPU__gesummv(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *x, DATA_TYPE *y,
                  DATA_TYPE *tmp) {
    int i;
    int j;
    dummyMethod1();
    for (i = 0; i <= 8191; i += 1) {
        tmp[i] = 0;
        y[i] = 0;
        for (j = 0; j <= 8191; j += 1) {
            tmp[i] = A[i * 8192 + j] * x[j] + tmp[i];
            y[i] = B[i * 8192 + j] * x[j] + y[i];
        }
        y[i] = 43532.0f * tmp[i] + 12313.0f * y[i];
    }
    dummyMethod2();
    return;
}

void init(DATA_TYPE *A, DATA_TYPE *x) {
    int i;
    int j;
    dummyMethod3();
    for (i = 0; i <= 8191; i += 1) {
        x[i] = ((DATA_TYPE)i) / 8192;

#pragma omp parallel for private(j)
        // #pragma rose_outline
        for (j = 0; j <= 8191; j += 1) {
            A[i * 8192 + j] = ((DATA_TYPE)i) * j / 8192;
        }
    }
    dummyMethod4();
}

void compareResults(DATA_TYPE *y, DATA_TYPE *y_outputFromGpu) {
    int i;
    int fail;
    fail = 0;
    dummyMethod3();
    for (i = 0; i <= 8191; i += 1) {
        if ((percentDiff(y[i], y_outputFromGpu[i])) > 0.05) {
            fail++;
        }
    }
    dummyMethod4();
    // Print results
    printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f "
           "Percent: %d\n",
           0.05, fail);
}

inline void update(DATA_TYPE *y_outputFromGpu) {
    DATA_TYPE yy = y_outputFromGpu[0];
}
// int main(int argc, char *argv[])

int main() {
    double t_start;
    double t_end;
    DATA_TYPE *A;
    DATA_TYPE *B;
    DATA_TYPE *x;
    DATA_TYPE *y;
    DATA_TYPE *y_outputFromGpu;
    DATA_TYPE *tmp;
    A = ((DATA_TYPE *)(malloc((8192 * 8192) * sizeof(DATA_TYPE))));
    B = ((DATA_TYPE *)(malloc((8192 * 8192) * sizeof(DATA_TYPE))));
    x = ((DATA_TYPE *)(malloc(8192 * sizeof(DATA_TYPE))));
    y = ((DATA_TYPE *)(malloc(8192 * sizeof(DATA_TYPE))));
    y_outputFromGpu = ((DATA_TYPE *)(malloc(8192 * sizeof(DATA_TYPE))));
    tmp = ((DATA_TYPE *)(malloc(8192 * sizeof(DATA_TYPE))));
    printf("<< Scalar, Vector and Matrix Multiplication >>\n");
    printf("Data size N: %d\n", 8192);
    init(A, x);
    //   t_start = rtclock();
    //   GPU__gesummv(A, B, x, y_outputFromGpu, tmp);
    //   update(y_outputFromGpu);
    //   t_end = rtclock();
    //   printf("GPU Runtime: %0.6lfs\n", t_end - t_start);
    t_start = rtclock();
    gesummv(A, B, x, y, tmp);
    t_end = rtclock();
    printf("CPU Runtime: %0.6lfs\n", t_end - t_start);
    // compareResults(y, y_outputFromGpu);
    free(A);
    free(B);
    free(x);
    free(y);
    free(y_outputFromGpu);
    free(tmp);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
