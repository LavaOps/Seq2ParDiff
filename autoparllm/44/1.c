#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// data race EXISTS

int main() {
    double a[10][10];
    for (int d = 0; d < 1; d++) {
        int j;
        dummyMethod1();
        for (int i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                a[i][j] = 0;
                dummyMethod2();
#pragma omp parallel for
                // #pragma rose_outline
                for (int k = 0; k < 10; k++) {
                    a[j][k] = 1;
                }
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                printf("a[%d][%d]=%f\n", j, k, a[j][k]);
            }
        }
    }
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }