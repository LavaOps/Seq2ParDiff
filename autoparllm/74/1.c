#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void abort();

int bar() {
    int a = 0;
    int i;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : a)
    // #pragma rose_outline
    for (i = 0; i <= 9; i += 1) {
        a += i;
    }
    printf("%d", a);
    fflush(stdout);
    return a;
    dummyMethod2();
}

int main() {
    int res;
    res = bar();
    if (res != 45)
        abort();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
