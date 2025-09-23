/*
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
!!! Copyright (c) 2017-20, Lawrence Livermore National Security, LLC
!!! and DataRaceBench project contributors. See the DataRaceBench/COPYRIGHT file
for details.
!!!
!!! SPDX-License-Identifier: (BSD-3-Clause)
!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!
*/

/*This example is referred from DRACC by Adrian Schmitz et al.
Missing ordered directive causes data race pairs var@28:5:W vs. var@28:13:R
*/

#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100

int main() {
    int var[N];
    dummyMethod3();
#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i < N; i++) {
        var[i] = 0;
    }
    dummyMethod4();

    dummyMethod1();
    for (int i = 1; i < N; i++) {
        var[i] = var[i - 1] + 1;
    }
    for (int i = 0; i < N; i++) {
        printf("var[%d]=%d\n", i, var[i]);
    }
    dummyMethod2();

    dummyMethod3();
    for (int i = 0; i < N; i++) {
        if (var[i] != i) {
            printf("Data Race Present\n");
            return 0;
        }
    }
    dummyMethod4();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }