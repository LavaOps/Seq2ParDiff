// gcc -fopenmp matrixMultiplicationParallel.c
//./a.out
#include "omp.h"
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int a[2][2] = {(1), (1), (1), (1)};
    int b[2][2] = {(2), (2), (2), (2)};
    int c[2][2];
    int sum = 0;
    {
        dummyMethod1();

        for (int i = 0; i <= 1; i += 1) {
            for (int j = 0; j <= 1; j += 1) {

#pragma omp parallel for reduction(+ : sum)
                // #pragma rose_outline
                for (int k = 0; k <= 1; k += 1) {
                    sum += a[i][k] * b[k][j];
                }
                c[i][j] = sum;
                sum = 0;
            }
        }
        dummyMethod2();
    }
    dummyMethod3();
    for (int i = 0; i <= 1; i += 1) {
        for (int j = 0; j <= 1; j += 1) {
            printf("%d \n", c[i][j]);
        }
    }
    dummyMethod4();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
