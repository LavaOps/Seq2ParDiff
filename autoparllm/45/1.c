#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a[100];
int main() {
    int i;
    dummyMethod1();
    double do_it_all = 0;
#pragma omp parallel for reduction(* : do_it_all)
    // #pragma rose_outline
    for (i = 0; i < 100; i++)
        do_it_all *= a[i] + 1;
    printf("%f", do_it_all);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }