#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
#define N 50
#define CHUNKSIZE 5

int main() {
    int i;
    int chunk;
    float c[50];
    chunk = 5;
    dummyMethod1();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 49; i += 1) {
        c[i] = i;
    }
    for (i = 0; i <= 49; i += 1) {
        printf("c[%d]=%f\n", i, c[i]);
    }
    return 0;
    dummyMethod2();
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
