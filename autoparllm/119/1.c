#include <omp.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include <omp.h>
#endif
#define f(A) (4.0 / (1.0 + A * A))
const int n = 10000000;

int main(int argc, char **argv) {
    int i;
    double w;
    double x;
    double sum;
    double pi;
    clock_t t1;
    clock_t t2;
    struct timeval tv1;
    struct timeval tv2;
    struct timezone tz;
#ifdef _OPENMP
#endif
#ifdef _OPENMP
/* end omp parallel */
#endif

// #pragma omp barrier
#pragma rose_outline
    gettimeofday(&tv1, (&tz));
#ifdef _OPENMP
#endif
    t1 = clock();
    /* calculate pi = integral [0..1] 4/(1+x**2) dx */
    w = 1.0 / n;
    sum = 0.0;
    dummyMethod1();

#pragma omp parallel for private(x, i) reduction(+ : sum) firstprivate(n)
    // #pragma rose_outline
    for (i = 1; i <= n; i += 1) {
        x = w * (((double)i) - 0.5);
        sum = sum + 4.0 / (1.0 + x * x);
    }
    dummyMethod2();
    pi = w * sum;
    t2 = clock();
#ifdef _OPENMP
#endif
    gettimeofday(&tv2, (&tz));
    printf("computed pi = %24.16g\n", pi);
    printf("CPU time (clock)                = %12.4g sec\n",
           (t2 - t1) / 1000000.0);
#ifdef _OPENMP
#endif
    printf("wall clock time (gettimeofday)  = %12.4g sec\n",
           (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) * 1e-6);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
