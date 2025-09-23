#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int arr[100];
int nt = 12;

int main() {
    dummyMethod1();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= 99; i += 1) {
        arr[i] = i;
    }
    // Verify
    dummyMethod2();
    int errors = 0;
    dummyMethod3();

#pragma omp parallel for reduction(+ : errors)
    // #pragma rose_outline
    for (int i = 0; i <= 99; i += 1) {
        if (arr[i] != i)
            errors++;
    }
    dummyMethod4();
    if (!errors) {
        fprintf(stderr, "Success\n");
        return 0;
    } else {
        fprintf(stderr, "Failed\nErrors: %d\n", errors);
        return 1;
    }
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
