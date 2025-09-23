#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a[100][100];
int main() {
    int i, j;
    int add_sit = 0;
    dummyMethod1();
    for (i = 0; i < 100; i++)
#pragma omp parallel for reduction(+ : add_sit)
        // #pragma rose_outline
        for (j = 0; j < 100; j++)
            add_sit += a[i][j];
    printf("%d", add_sit);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }