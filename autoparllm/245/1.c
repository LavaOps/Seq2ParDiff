/* { dg-do run } */
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define EPS 0.0001
#define N 1024 * 1024

void init(float B[], float C[], int n) {
    int i;
    dummyMethod3();

#pragma omp parallel for private(i) firstprivate(n)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        B[i] = (0.1 * i);
        C[i] = (0.01 * i * i);
    }
}
int dummyMethod4();

float dotprod_ref(float B[], float C[], int n) {
    int i;
    float sum = 0.0;
    dummyMethod3();

#pragma omp parallel for private(i) reduction(+ : sum) firstprivate(n)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        sum += B[i] * C[i];
    }
    return sum;
    dummyMethod4();
}

float dotprod(float B[], float C[], int n) {
    int i;
    float sum = 0;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum) firstprivate(n)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        sum += B[i] * C[i];
    }
    dummyMethod2();
    return sum;
}

void check(float a, float b) {
    float err = b == 0.0 ? a : (a - b) / b;
    if (((err > 0 ? err : -err)) > 0.0001)
        abort();
}

int main() {
    float *v1 = (float *)(malloc((1024 * 1024) * sizeof(float)));
    float *v2 = (float *)(malloc((1024 * 1024) * sizeof(float)));
    float p1;
    float p2;
    init(v1, v2, 1024 * 1024);
    p1 = dotprod_ref(v1, v2, 1024 * 1024);
    p2 = dotprod(v1, v2, 1024 * 1024);
    printf("p1=%f, p2=%f", p1, p2);
    fflush(stdout);
    check(p1, p2);
    free(v1);
    free(v2);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
