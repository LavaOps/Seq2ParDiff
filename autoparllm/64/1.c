#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define ROW 1000

int main() {
    time_t start_time;
    time_t end_time;
    clock_t begin = clock();
    int **matrizA;
    int **matrizB;
    int **matrizC;
    int i = 0;
    int j = 0;
    int k = 0;
    matrizA = ((int **)(malloc(1000 * sizeof(int *))));
    matrizB = ((int **)(malloc(1000 * sizeof(int *))));
    matrizC = ((int **)(malloc(1000 * sizeof(int *))));
    dummyMethod3();
    for (i = 0; i <= 999; i += 1) {
        *(matrizA + i) = ((int *)(malloc(1000 * sizeof(int))));
        *(matrizB + i) = ((int *)(malloc(1000 * sizeof(int))));
        *(matrizC + i) = ((int *)(malloc(1000 * sizeof(int))));
    }
    dummyMethod4();
    dummyMethod3();

    for (i = 0; i <= 999; i += 1) {

#pragma omp parallel for private(j)
        // #pragma rose_outline
        for (j = 0; j <= 999; j += 1) {
            matrizA[i][j] = 1;
            matrizB[i][j] = 1;
        }
    }
    dummyMethod4();
    start_time = time(((void *)0));
    dummyMethod1();

    for (i = 0; i <= 999; i += 1) {

        for (j = 0; j <= 999; j += 1) {
            int sum = 0;

#pragma omp parallel for private(k) reduction(+ : sum)
            // #pragma rose_outline
            for (k = 0; k <= 999; k += 1) {
                sum += matrizA[i][k] * matrizB[k][j];
            }
            matrizC[i][j] = sum;
        }
    }
    dummyMethod2();
    end_time = time(((void *)0));
    clock_t end = clock();
    printf("time %lf\n", ((double)(end - begin)) / ((__clock_t)1000000) / 4);
    /*for(i = 0; i < ROW; i++){
                    for(j = 0; j < ROW; j++){
                            printf("%i ", matrizC[i][j]);
                    }
                    printf("\n");
            }*/
    dummyMethod3();
    for (i = 0; i <= 999; i += 1) {
        free(matrizA[i]);
        free(matrizB[i]);
        free(matrizC[i]);
    }
    dummyMethod4();
    free(matrizA);
    free(matrizB);
    free(matrizC);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
