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
    /* Initialization of the vectors */
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= 102399; i += 1) {
        vecA[i] = 1.0 / ((double)(102400 - i));
        vecB[i] = vecA[i] * vecA[i];
    }
    dummyMethod4();
    double res = 0.0;
    dummyMethod1();

#pragma omp parallel for reduction(+ : res)
    // #pragma rose_outline
    for (int i = 0; i <= 102399; i += 1) {
        res += vecA[i] * vecB[i];
    }
    dummyMethod2();
    printf("Dot product: %18.16f\n", res);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
