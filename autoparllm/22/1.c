#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(void) {
    const long N = 1000000;
    int i, a[N];
    int add_it = 0;
    dummyMethod1();
#pragma omp parallel for reduction(+ : add_it)
    // #pragma rose_outline
    for (i = 0; i < N; i++)
        add_it += 2 * a[i];
    printf("%d", add_it);

    return 0;
    dummyMethod2();

    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }