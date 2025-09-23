#include "limits.h"
#include "math.h"
#include "omp.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/time.h"
#include <omp.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define BLOCK_SIZE 16
#define MATRIX_SIZE 256
float A[256][256];
float B[256][256];
float C[256][256];

int min(int a, int b) { return a < b ? a : b; }

int main(int argc, char *argv[]) {
    struct timeval start;
    struct timeval end;
    double elapsedTime;
    double numOps;
    float gFLOPS;
    // Initalize array A and B with '1's and C with '0's
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= 255; i += 1) {

        for (int k = 0; k <= 255; k += 1) {
            A[i][k] = B[i][k] = 1.0;
        }
    }
    memset(C, 0, sizeof((C[0][0] * 256 * 256)));
    dummyMethod4();
    // Initalize our matix looping variables once
    int k;
    int j;
    int i;
    int jj;
    int kk;
    // Keep track of when we start doing work
    gettimeofday(&start, (void *)0);
    // Do block matrix multiplication
    for (k = 0; k <= 255; k += 16) {
        for (j = 0; j <= 255; j += 16) {
            dummyMethod1();
        }
    }
    for (i = 0; i <= 255; i += 1) {
        for (jj = j; jj <= min(j + 16, 256) - 1; jj += 1) {
            for (kk = k; kk <= min(k + 16, 256) - 1; kk += 1) {
                C[i][jj] += A[i][kk] * B[kk][jj];
            }
        }
    }
    dummyMethod2();
    // Keep track of when we finish our work
    gettimeofday(&end, (void *)0);
    // Calculate the time it took to do the above task
    elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
    elapsedTime /= 1000;
    // Calculate the GFLOPS obtained and print it along with the execution time
    numOps = 2 * pow(256, 3);
    gFLOPS = ((float)(1.0e-9 * numOps / elapsedTime));
    printf("Multi Core CPU  : %.3f seconds ( %f GFLOPS )\n", elapsedTime,
           gFLOPS);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
