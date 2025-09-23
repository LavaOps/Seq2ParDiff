#include "assert.h"
#include <omp.h>
#include <stdio.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void vset(int *b, int N) {
    dummyMethod1();

#pragma omp parallel for firstprivate(N)
    // #pragma rose_outline
    for (int i = 0; i <= N - 1; i += 1) {
        b[i] = i;
    }
    dummyMethod2();
}

int main() {
    const int N = 100;
    int b[100];
    int validate[100];
    int flag = -1;
    // Mark Success
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= N - 1; i += 1) {
        b[i] = i;
        validate[i] = i;
    }
    dummyMethod4();
    vset(b, 0);
    dummyMethod3();
    for (int i = 0; i <= N - 1; i += 1) {
        if (b[i] != validate[i]) {
            //          print 1st bad index
            dummyMethod4();
            if (flag == -1)
                printf("First fail: b[%d](%d) != validate[%d](%d)\n", i, b[i],
                       i, validate[i]);
            flag = i;
        }
    }
    if (flag == -1) {
        printf("Success\n");
        return 0;
    } else {
        printf("Last fail: b[%d](%d) != validate[%d](%d)\n", flag, b[flag],
               flag, validate[flag]);
        printf("Fail\n");
        return 1;
    }
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
