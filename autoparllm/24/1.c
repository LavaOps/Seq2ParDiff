#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 12

int main(void) {

    int i, A[N];

    dummyMethod3();
#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i < N; i++)
        A[i] = i;

    dummyMethod4();
    dummyMethod1();
#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i < N; i++)
        A[i] += 1;

    for (i = 0; i < N; i++)
        printf("A[%d] = %d\n", i, A[i]);
    dummyMethod2();
    dummyMethod3();

    return 0;
    dummyMethod4();
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }