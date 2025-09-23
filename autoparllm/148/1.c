/*
compilation:
clang -pedantic -Wall -o omp-ser-cl omp-ser.c -fopenmp=libomp
-fopenmp-targets=nvptx64-nvidia-cuda -L/usr/local/cuda/lib64
--cuda-path=/usr/local/cuda minimal compilation command: clang  -o omp-ser-cl
omp-ser.c -fopenmp=libomp -fopenmp-targets=nvptx64-nvidia-cuda source: based on
"OpenMP Application Programming Interface Examples - Version 5.0.0 - November
2019" Section 4.7.1 'Simple target data Construct'
*/
#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    const int N = 1000000;
    unsigned int i;
    unsigned int j;
    float *a;
    float *b;
    float *c;
    a = ((float *)(malloc(N * sizeof(float))));
    b = ((float *)(malloc(N * sizeof(float))));
    c = ((float *)(malloc(N * sizeof(float))));
    // srand((unsigned int)time(NULL));
    dummyMethod3();
    for (i = 0; i <= ((unsigned int)N) - 1; i += 1) {
        a[i] = 0;
        b[i] = ((((float)(rand())) / ((float)2147483647)) * 4.0);
        c[i] = ((((float)(rand())) / ((float)2147483647)) * 4.0);
    }
    dummyMethod4();
    {
        dummyMethod1();

#pragma omp parallel for private(j) firstprivate(N)
        // #pragma rose_outline
        for (j = 0; j <= ((unsigned int)N) - 1; j += 1) {
            a[j] = (b[j] + 3.73 * c[j]);
        }
        for (j = 0; j <= ((unsigned int)N) - 1; j += 1) {
            printf("a[%d]=%f\n", j, a[j]);
        }
        dummyMethod2();
    }
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
