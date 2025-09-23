#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define n 100
int a[n];
int main() {
    int i, j;
    j = 10;
    dummyMethod1();
    int two_it = 0;
#pragma omp parallel for reduction(* : two_it)
    // #pragma rose_outline
    for (i = 1; i <= n; i++) {
        two_it = two_it * j;
    }
    printf("%d", two_it);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }