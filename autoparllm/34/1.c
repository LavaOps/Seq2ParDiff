#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char *argv[]) {
    int i;
    int len = 1000;
    int a[1000];

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i < len; i++)
        a[i] = i;

    dummyMethod3();
    for (i = 0; i < len - 1; i++)
        a[i] = a[i + 1] + 1;

    for (i = 0; i < len; i++)
        printf("a[%d]=%d\n", i, a[i]);

    dummyMethod4();
    return 0;
    dummyMethod2();
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }