// Test the handling of two loops under omp for
// watch the loop index replacement (private by default)
// and tje array outlining
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(void) {
    int i, j;
    float **u = (float **)malloc(500 * sizeof(float *));
    dummyMethod3();
#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i < 500; i++)
        u[i] = (float *)malloc(500 * sizeof(float));

    dummyMethod4();
    dummyMethod1();
#pragma omp parallel for private(i, j)
    // #pragma rose_outline
    for (i = 0; i < 500; i++)
        for (j = 0; j < 500; j++) {
            u[i][j] = 0.0;
        }
    for (i = 0; i < 500; i++)
        for (j = 0; j < 500; j++) {
            printf("u[%d][%d]=%f\n", i, j, u[i][j]);
        }

    return 0;
    dummyMethod2();
}
// This code has data races since j is shared
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }