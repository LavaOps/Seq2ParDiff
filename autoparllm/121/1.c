#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/*
MIT License
Copyright (c) 2019 NOUREDDINE DAGHBOUDJ
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions: The above copyright notice and this
permission notice shall be included in all copies or substantial portions of the
Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#define N 1024

void initArray(unsigned int *array, unsigned int size) {
    dummyMethod3();
    for (unsigned int i = 0; i <= size - 1; i += 1) {
        array[i] = (rand() % 40 + 10);
    }
}
int dummyMethod4();

void printArray(unsigned int *array, unsigned int size) {
    dummyMethod3();
    for (unsigned int i = 0; i <= size - 1; i += 1) {
        printf("%i ", array[i]);
    }
    printf("\n");
    dummyMethod4();
}

unsigned int sumArray(unsigned int *A, unsigned int size) {
    unsigned int sum = 0;
    dummyMethod1();

#pragma omp parallel for reduction(+ : sum) firstprivate(size)
    // #pragma rose_outline
    for (unsigned int i = 0; i <= size - 1; i += 1) {
        sum += A[i];
    }
    dummyMethod2();
    return sum;
}

int main() {
    unsigned int a[1024];
    unsigned int b[1024];
    unsigned int c[1024];
    srand(0);
    initArray(a, 1024);
    printf("sum(A) = %i\n", (sumArray(a, 1024)));
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
