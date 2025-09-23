#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NX 102400

int main() {
    double vecA[102400];
    double vecB[102400];
    double vecC[102400];
    double sum;
    int i;
    /* Initialization of the vectors */
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 102399; i += 1) {
        vecA[i] = 1.0 / ((double)(102400 - i));
        vecB[i] = vecA[i] * vecA[i];
    }
    dummyMethod4();
    dummyMethod1();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 102399; i += 1) {
        vecC[i] = vecA[i] + vecB[i];
    }
    dummyMethod2();
    sum = 0.0;
    /* Compute the check value */
    dummyMethod3();

#pragma omp parallel for private(i) reduction(+ : sum)
    // #pragma rose_outline
    for (i = 0; i <= 102399; i += 1) {
        sum += vecC[i];
    }
    dummyMethod4();
    printf("Reduction sum: %18.16f\n", sum);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
