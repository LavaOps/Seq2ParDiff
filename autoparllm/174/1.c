#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NX 102400

int main() {
    long vecA[102400];
    long sum;
    long psum;
    long sumex;
    int i;
    /* Initialization of the vectors */
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 102399; i += 1) {
        vecA[i] = ((long)i) + 1;
    }
    dummyMethod4();
    sumex = ((long)102400) * (102400 + 1) / ((long)2);
    printf("Arithmetic sum formula (exact):                  %ld\n", sumex);
    sum = 0.0;
    /* Version with data race */
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum)
    // #pragma rose_outline
    for (i = 0; i <= 102399; i += 1) {
        sum += vecA[i];
    }
    dummyMethod2();
    printf("Sum with data race:                              %ld\n", sum);
    sum = 0.0;
    /* Dot product using critical section = SERIAL CODE! */
    dummyMethod3();

#pragma omp parallel for private(i) reduction(+ : sum)
    // #pragma rose_outline
    for (i = 0; i <= 102399; i += 1) {
        sum += vecA[i];
    }
    dummyMethod4();
    printf("Sum using critical section:                      %ld\n", sum);
    sum = 0.0;
    /* Dot product using private partial sums and critical section */
    {
        psum = 0.0;
        dummyMethod3();

#pragma omp parallel for private(i) reduction(+ : psum)
        // #pragma rose_outline
        for (i = 0; i <= 102399; i += 1) {
            psum += vecA[i];
        }
        dummyMethod4();
        sum += psum;
    }
    printf("Sum using private variable and critical section: %ld\n", sum);
    sum = 0.0;
    /* Dot product using reduction */
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : sum)
    // #pragma rose_outline
    for (i = 0; i <= 102399; i += 1) {
        sum += vecA[i];
    }
    dummyMethod2();
    printf("Reduction sum:                                   %ld\n", sum);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
