/* Programa e6.c */
#include "stdio.h"
#include "stdlib.h"
#include <omp.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1000

float producto(float *a, float *b, int n) {
    float sum = 0.0;
    dummyMethod1();

#pragma omp parallel for reduction(+ : sum) firstprivate(n)
    // #pragma rose_outline
    for (int i = 0; i <= n - 1; i += 1) {
        sum += a[i] * b[i];
    }
    dummyMethod2();
    return sum;
}

int main() {
    float total = 0;
    float a[1000];
    float b[1000];
    int k = 0;
    dummyMethod3();

#pragma omp parallel for private(k)
    // #pragma rose_outline
    for (k = 0; k <= 999; k += 1) {
        a[k] = k;
        b[k] = k;
    }
    dummyMethod4();
    total = producto(a, b, 1000);
    printf("%.6f \n", total);
    int s;
    int r;
    int t;
    dummyMethod3();
    for (int i = 0; i <= 999; i += 1) {
        s = a[i];
        r = b[i];
        t = (a[i] * b[i]);
        printf("%d ", r);
        printf(" * %d ", s);
        printf(" = %d \n", t);
    }
    dummyMethod4();
    exit(0);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
