#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, const char *argv[]) {
    double pi;
    double x;
    int i;
    int N;
    pi = 0.0;
    N = 1000;
    dummyMethod1();

#pragma omp parallel for private(x, i) reduction(+ : pi)
    // #pragma rose_outline
    for (i = 0; i <= N - 1; i += 1) {
        x = ((double)i) / N;
        pi += 4 / (1 + x * x);
    }
    dummyMethod2();
    pi = pi / N;
    printf("%f\n", pi);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
