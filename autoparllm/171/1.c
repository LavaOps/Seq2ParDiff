#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int a[10];
    int b[10];
    int c[10];
    int n = 10;
    int i;
    dummyMethod1();

#pragma omp parallel for private(i) firstprivate(n)
    // #pragma rose_outline
    for (i = 0; i <= n - 1; i += 1) {
        c[i] = a[i] + b[i];
    }
    dummyMethod2();
    printf("Depois da regi\303\243o paralela ... i = %d\n", i);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
