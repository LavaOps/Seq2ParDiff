#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/*
 * Combined parallel for
 * with multiple clauses
 * */

int main() {
    int i;
    int a[1000];
    int sum;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum)
    // #pragma rose_outline
    for (i = 0; i <= 999; i += 1) {
        a[i] = i * 2;
        sum += i;
    }
    for (i = 0; i <= 999; i += 1) {
        printf("a[%d]=%d\n", i, a[i]);
    }
    printf("%d", sum);
    dummyMethod2();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
