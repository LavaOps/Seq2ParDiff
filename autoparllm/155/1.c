/*
<testinfo>
test_generator=config/mercurium-iomp
</testinfo>
*/
#include <stdio.h>
#include "omp.h"
#include <assert.h>
#include <omp.h>
#include <stdint.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

struct A {
    int *p;
    int N;
};

void neutral_init(struct A *var) {
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= var->N - 1; i += 1) {
        var->p[i] = 0;
    }
}
int dummyMethod4();

void comb(struct A *out, struct A *in) {
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= out->N - 1; i += 1) {
        out->p[i] += in->p[i];
    }
}
int dummyMethod4();

void init(struct A *priv, struct A *orig) {
    priv->p = (malloc((orig->N) * sizeof((*priv->p))));
    priv->N = orig->N;
    neutral_init(priv);
}

int main(int argc, char *argv[]) {
    struct A var;
    var.N = 10;
    //! Assume that this value is something we don't know at compile time!
    var.p = (malloc(var.N * sizeof((*var.p))));
    neutral_init(&var);
    int mat[20][10];
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= 19; i += 1) {

#pragma omp parallel for
        // #pragma rose_outline
        for (int j = 0; j <= 9; j += 1) {
            mat[i][j] = j * 20 + i;
        }
    }
    for (int i = 0; i <= 19; i += 1) {
        for (int j = 0; j <= 9; j += 1) {
            printf("mat[%d][%d]=%d\n", i, j, mat[i][j]);
        }
    }
    dummyMethod4();
    dummyMethod1();
    for (int i = 0; i <= 19; i += 1) {

#pragma omp parallel for
        // #pragma rose_outline
        for (int j = 0; j <= 9; j += 1) {
            var.p[j] += mat[i][j] + 1;
        }
    }
    for (int i = 0; i <= 19; i += 1) {
        for (int j = 0; j <= 9; j += 1) {
            printf("var.p[%d]=%d\n", j, var.p[j]);
        }
    }
    dummyMethod2();
    int check = 0;
    dummyMethod3();

#pragma omp parallel for reduction(+ : check)
    // #pragma rose_outline
    for (int i = 0; i <= var.N - 1; i += 1) {
        check += var.p[i];
    }
    printf("check=%d\n", check);
    fflush(stdout);
    dummyMethod4();
    (((void)(sizeof((((check = 200 * 199 / 2 + 200) ? 1 : 0))))), (({
         if (check = 200 * 199 / 2 + 200)
             ;
         else
             __assert_fail("check = 200*199/2 + 200",
                           "bsc-pm_nanox_success_for_reduction_07.c", 70,
                           __PRETTY_FUNCTION__);
     })));
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
