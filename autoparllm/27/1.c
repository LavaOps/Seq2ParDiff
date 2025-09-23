#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a[100][100];
int main() {
    int i, j;
    int sum_add = 0;
    dummyMethod1();
    for (i = 0; i < 100; i++)
#pragma omp parallel for reduction(+ : sum_add)
        // #pragma rose_outline
        for (j = 0; j < 100; j++)
            sum_add += a[i][j] + 1;
    printf("%d", sum_add);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }