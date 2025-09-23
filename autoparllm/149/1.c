#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int x = 10;
    int a;
    dummyMethod1();

#pragma omp parallel for private(x) reduction(- : a)
    // #pragma rose_outline
    for (x = 0; x <= 9; x += 1) {
        a -= 10;
    }
    printf("%d", a);
    dummyMethod2();
    x = 20;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
