// COMP 4510, A5, Q2
// Noah Redden, 7841009
#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100
int a[100][100];
int b[100][100];
int c[100][100];
struct timeb tstart;
struct timeb tend;
int tdelta;

int main(int argc, char *argv[]) {
    ftime(&tstart);
    printf("N: %i\n", 100);
    // initialize arrays
    dummyMethod1();

    for (int i = 0; i <= 99; i += 1) {

#pragma omp parallel for
        // #pragma rose_outline
        for (int j = 0; j <= 99; j += 1) {
            a[i][j] = 1;
            b[i][j] = 2;
            c[i][j] = 0;
        }
    }
    dummyMethod2();
    dummyMethod1();
    for (int i = 0; i <= 99; i += 1) {
        for (int j = 0; j <= 99; j += 1) {
            int sum = 0;

#pragma omp parallel for reduction(+ : sum)
            // #pragma rose_outline
            for (int k = 0; k <= 99; k += 1) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
    dummyMethod2();
    // print array
    dummyMethod3();
    for (int i = 0; i <= 99; i += 1) {
        for (int j = 0; j <= 99; j += 1) {
            printf("[%i] ", c[i][j]);
        }
        printf("\n");
    }
    dummyMethod4();
    ftime(&tend);
    tdelta = ((int)(1000.0 * (tend.time - tstart.time))) +
             (tend.millitm - tstart.millitm);
    printf("\nTime: %ims\n", tdelta);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
