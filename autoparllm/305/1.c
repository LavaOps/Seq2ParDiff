#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a[100][100];
int main() {
    int i, j;
    dummyMethod1();
    double dd = 0;
    for (i = 0; i < 100; i++)
#pragma omp parallel for reduction(+ : dd)
        // #pragma rose_outline
        for (j = 0; j < 100; j++)
            dd = dd + 1;
    printf("%f", dd);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }