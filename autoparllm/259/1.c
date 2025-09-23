/*
1. A local copy of reduction variable  is made and initialized depending on the
op(e.g. 0 for +).
2. Compiler finds standard reduction expressions containing op and uses them to
update the local copy.
3. Local copies are reduced into a single value and combined with the original
global value.
*/
#include <assert.h>
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

int main() {
    int i;
    long sum = 0;
    int upper = 100;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum)
    // #pragma rose_outline
    for (i = 1; i <= upper; i += 1) {
        sum = sum + i;
    }
    dummyMethod2();
    printf("sum from 1 to %d is %ld\n", upper, sum);
    (((void)(sizeof(((sum == 5050 ? 1 : 0))))), (({
         if (sum == 5050)
             ;
         else
             __assert_fail("sum==5050",
                           "rose-compiler_rose_reduction-classic.c", 29,
                           __PRETTY_FUNCTION__);
     })));
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
