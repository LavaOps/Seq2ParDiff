#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define n 100
int a[n];
int main() {
    int i, j;
    j = 0;
    float not_a = 0;
    dummyMethod1();
#pragma omp parallel for reduction(+ : j)
    // #pragma rose_outline
    for (i = 1; i <= n; i++) {
        j = j + 1;
        not_a *= a[i] + 1;
    }
    printf("%d\n%f", j, not_a);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }