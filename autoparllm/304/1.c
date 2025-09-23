#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a[100];
int main() {
    int i;
    dummyMethod1();
    int ty_i_a = 0;
#pragma omp parallel for reduction(* : ty_i_a)
    // #pragma rose_outline
    for (i = 0; i < 100; i++)
        ty_i_a = ty_i_a * 2;
    printf("%d", ty_i_a);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }