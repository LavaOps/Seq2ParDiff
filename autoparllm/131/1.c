#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1000000ll
#define SUM (N * (N - 1) / 2)

int main() {
    {
        long long a;
        long long i;
        a = 0;
        dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : a)
        // #pragma rose_outline
        for (i = 0; i <= 1000000ll - 1; i += 1) {
            a += i;
        }
        dummyMethod2();
        {
            if (a != 1000000ll * (1000000ll - 1) / 2)
                printf("Incorrect result = %lld, expected = %lld!\n", a,
                       1000000ll * (1000000ll - 1) / 2);
            else
                printf("The result is correct = %lld!\n", a);
        }
    }
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
