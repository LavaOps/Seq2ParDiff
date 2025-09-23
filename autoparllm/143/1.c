#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX 10000000

int main() {
    size_t i;
    int n = 0;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : n)
    // #pragma rose_outline
    for (i = 0; i <= ((unsigned long)10000000) - 1; i += 1) {
        n++;
    }
    printf("n = %d\n", n);
    dummyMethod2();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
