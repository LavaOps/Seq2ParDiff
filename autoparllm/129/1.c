#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
const int N = 128 * 2;

int main(int argc, char **argv) {
    float matA[256][256];
    float matB[256][256];
    float matC[256][256];
    float matE[256][256];
    fprintf(stderr, "Starting matmul\n");
    {
        float tmp;
        dummyMethod1();

        for (int i = 0; i <= N - 1; i += 1) {

            for (int j = 0; j <= N - 1; j += 1) {
                tmp = 0.0;

#pragma omp parallel for reduction(+ : tmp)
                // #pragma rose_outline
                for (int k = 0; k <= N - 1; k += 1) {
                    tmp += matA[i][k] * matB[k][j];
                }
                matC[i][j] = tmp;
            }
        }
        dummyMethod2();
    }
    fprintf(stderr, "Passed\n");
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
