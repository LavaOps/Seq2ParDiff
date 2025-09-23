#include <math.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 30
#define numThreads 2
double A[30][30];
double B[30];
double X[30];

struct reduceRowArgs {
    int arg1;
    int arg2;
};
void gauss();
void *reduceRow(void *s);

void initialize() {
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 5;
    A[1][1] = 6;
    A[1][2] = 7;
    A[2][0] = 9;
    A[2][1] = 1;
    A[2][2] = 2;
    B[0] = 4;
    B[1] = 8;
    B[2] = 3;
    X[0] = 0.0;
    X[0] = 0.0;
    X[0] = 0.0;
}

void randinit() {
    double initial = drand48();
    int i;
    int j;
    dummyMethod3();
    for (i = 0; i <= 29; i += 1) {
        for (j = 0; j <= 29; j += 1) {
            A[i][j] = drand48();
        }
        B[i] = drand48();
        X[i] = 0.0;
    }
    dummyMethod4();
}

int main() {
    int i;
    int j;
    // initialize();
    randinit();
    dummyMethod3();
    for (i = 0; i <= 29; i += 1) {
        for (j = 0; j <= 29; j += 1) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
    dummyMethod4();
    dummyMethod3();
    for (i = 0; i <= 29; i += 1) {
        printf("%f\n", B[i]);
    }
    dummyMethod4();
    printf("\n");
    gauss();
    dummyMethod3();
    for (i = 0; i <= 29; i += 1) {
        for (j = 0; j <= 29; j += 1) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
    dummyMethod4();
    printf("\n");
    dummyMethod3();
    for (i = 0; i <= 29; i += 1) {
        printf("%f\n", X[i]);
    }
    dummyMethod4();
    return 0;
}

void gauss() {
    int i;
    int row;
    int col;
    double ratio;
    for (i = 0; i <= 28; i += 1) {
        dummyMethod1();
        for (row = i + 1; row <= 29; row += 1) {
            ratio = A[row][i] / A[i][i];

#pragma omp parallel for private(col)
            // #pragma rose_outline
            for (col = i; col <= 29; col += 1) {
                A[row][col] -= ratio * A[i][col];
            }
            B[row] -= ratio * B[i];
        }
        dummyMethod2();
    }
    // Back sub
    for (row = 30 - 1; row >= 0; row += -1) {
        X[row] = B[row];
        for (col = 30 - 1; col >= row + 1; col += -1) {
            X[row] -= A[row][col] * X[col];
        }
        X[row] /= A[row][row];
    }
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
