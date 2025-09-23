#include "omp.h"
#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 800
float A[800][800];
float B[800][800];
float C1[800][800];
float C2[800][800];

int main() {
    int i;
    int j;
    int k;
    srand((time(((void *)0))));
    dummyMethod3();
    for (i = 0; i <= 799; i += 1) {
        for (j = 0; j <= 799; j += 1) {
            A[i][j] = (rand() % 10);
            B[i][j] = (rand() % 10);
        }
    }
    dummyMethod4();
    /* sequential version. For testing purposes only */
    /*for(i=0; i<N; i++) {
              for(j=0; j<N; j++) {
                  C1[i][j] = 0.;
                  for(k=0; k<N; k++) {
                      C1[i][j] += A[i][k]*B[k][j];
                  }
              }
        }*/
    /* parallel version using OpenMP */
    float m_result;
    for (i = 0; i <= 799; i += 1) {
        for (j = 0; j <= 799; j += 1) {
            m_result = 0.0;
            dummyMethod1();

#pragma omp parallel for private(k) reduction(+ : m_result)
            // #pragma rose_outline
            for (k = 0; k <= 799; k += 1) {
                m_result += A[i][k] * B[k][j];
            }
            dummyMethod2();
            C2[i][j] = m_result;
        }
    }
    for (i = 0; i <= 799; i += 1) {
        for (j = 0; j <= 799; j += 1) {
            printf("C2[%d][%d]=%f\n", i, j, C2[i][j]);
        }
    }
    /* verify that calculations are correct */
    /*for(i=0; i<N; i++) {
            for(j=0; j<N; j++)
                assert(C1[i][j] == C2[i][j]);
        }*/
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
