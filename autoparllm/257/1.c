#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// NO data race

int main() {
    double a[10][10];
    for (int d = 0; d <= 0; d += 1) {
        dummyMethod1();

        for (int i = 0; i <= 9; i += 1) {
            for (int j = 0; j <= 9; j += 1) {
                a[i][j] = 0;

#pragma omp parallel for
                // #pragma rose_outline
                for (int k = 0; k <= 9; k += 1) {
                    a[i][k] = 1;
                }
            }
        }
        dummyMethod2();
    }
    for (int d = 0; d <= 0; d += 1) {
        for (int i = 0; i <= 9; i += 1) {
            for (int j = 0; j <= 9; j += 1) {
                for (int k = 0; k <= 9; k += 1) {
                    printf("a[%d][%d]=%f\n", i, k, a[i][k]);
                }
            }
        }
    }
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
