#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#endif

int a[11][11];
int main(void) {
    int i, j;
    int m = 10;
    int n = 10;

    dummyMethod3();
#pragma omp parallel for private(i, j)
    // #pragma rose_outline
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 11; j++) {
            a[i][j] = 0;
        }
    }
    dummyMethod4();

    dummyMethod1();

    for (i = 1; i < m; i += 1) {
        for (j = 1; j < n; j += 1) {
            int k = 3;
            int l = 3;
            int z = 3;
            a[i][j] = i + j + l + k + z;
        }
    }
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 11; j++) {
            printf("a[%d][%d]=%d\n", i, j, a[i][j]);
        }
    }
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }