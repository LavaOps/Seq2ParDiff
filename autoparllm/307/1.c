#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a[100][100];
int main() {
    int i, j;
    float curr_x = 0;
    dummyMethod1();
    for (i = 0; i < 100; i++)
#pragma omp parallel for reduction(* : curr_x)
        // #pragma rose_outline
        for (j = 0; j < 100; j++)
            curr_x = curr_x * 1;
    printf("%f", curr_x);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }