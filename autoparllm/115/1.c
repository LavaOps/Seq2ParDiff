#include "omp.h"
#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, (void *)0);
    return tv.tv_sec + 1e-6 * tv.tv_usec;
}
/*******************************************************************************
 * Sin(x) Taylor Series
 ********************************************************************************
 *           oo  (-1)^n                -1         1           -1
 * sin(x) = Sum ------- x^(2n+1) = x + -- x^3 + ----- x^5 + ------- x^7 + ...
 *          n=0 (2n+1)!                 6       5*4*6       7*6*120
 ********************************************************************************/

void sinx(int N, int terms, float *x, float *y) {
    int i;
    int j;
    dummyMethod1();

#pragma omp parallel for private(i, j) firstprivate(N, terms)
    // #pragma rose_outline
    for (i = 0; i <= N - 1; i += 1) {
        float value = x[i];
        float numer = x[i] * x[i] * x[i];
        long long denom = 6;
        int sign = -1;
        for (j = 1; j <= terms; j += 1) {
            value += sign * numer / denom;
            numer *= x[i] * x[i];
            denom *= ((2 * j + 2) * (2 * j + 3));
            sign *= -1;
        }
        y[i] = value;
    }
    dummyMethod2();
}

int main(int argc, char *argv[]) {
    int N;
    int terms;
    int i;
    int delta;
    int plot;
    float *x;
    float *y;
    double dtime;
    FILE *res;
    if (argc == 4) {
        N = atoi(argv[1]);
        terms = atoi(argv[2]);
        plot = 1;
    } else if (argc == 3) {
        N = atoi(argv[1]);
        terms = atoi(argv[2]);
        plot = 0;
    } else {
        printf("*** Use: %s N terms [-p] ***\n", argv[0]);
        printf("*    Ex: %s 131072 12 -p   \n", argv[0]);
        printf("*    -p: plots results     \n");
        return 0;
    }
    printf("Using N=%d and terms=%d (%s).\n", N, terms,
           (plot ? "Plot" : "No plot"));
    x = ((float *)(malloc(N * sizeof(float))));
    (((void)(sizeof(((x ? 1 : 0))))), (({
         if (x)
             ;
         else
             __assert_fail("x", "MLRivero_Pthread-OpenMP-assignment_sinx-p.c",
                           69, __PRETTY_FUNCTION__);
     })));
    y = ((float *)(malloc(N * sizeof(float))));
    (((void)(sizeof(((y ? 1 : 0))))), (({
         if (y)
             ;
         else
             __assert_fail("y", "MLRivero_Pthread-OpenMP-assignment_sinx-p.c",
                           71, __PRETTY_FUNCTION__);
     })));
    // X from -1.5*pi to 1.5*pi
    dummyMethod3();
    for (i = 0; i <= N - 1; i += 1) {
        x[i] = (-1.5 * 3.14159265358979323846 +
                (i * 3) * 3.14159265358979323846 / N);
    }
    dummyMethod4();
    dtime = gettime();
    sinx(N, terms, x, y);
    dtime = gettime() - dtime;
    printf("Exec time: %9.5f sec.\n", dtime);
    if (plot) {
        // Openning the file to write the results (x,y), for gnuplot input
        res = fopen("sinx.txt", "w");
        (((void)(sizeof(((res ? 1 : 0))))), (({
             if (res)
                 ;
             else
                 __assert_fail("res",
                               "MLRivero_Pthread-OpenMP-assignment_sinx-p.c",
                               90, __PRETTY_FUNCTION__);
         })));
        delta = 1;
        // For plotting we do not need too many points
        if (N > 1000)
            delta = N / 1000;
        dummyMethod3();
        for (i = 0; i <= N - 1; i += delta) {
            fprintf(res, "%2.5f %2.5f\n", x[i], y[i]);
        }
        dummyMethod4();
        fclose(res);
        // Calling gnuplot from command line
        // Using pause for the window not to close right away (close with a
        // click)
        (((void)(sizeof(((system("gnuplot -e \"plot 'sinx.txt' with lines; "
                                 "pause mouse any\"") != -1
                              ? 1
                              : 0))))),
         (({
             if (system("gnuplot -e \"plot 'sinx.txt' with lines; pause mouse "
                        "any\"") != -1)
                 ;
             else
                 __assert_fail("system(\"gnuplot -e \\\"plot 'sinx.txt' with "
                               "lines; pause mouse any\\\"\") != -1",
                               "MLRivero_Pthread-OpenMP-assignment_sinx-p.c",
                               104, __PRETTY_FUNCTION__);
         })));
    } else {
        printf("(x[0],y[0]) = (%1.4f,%1.4f); (x[N-1],y[N-1]) = (%1.4f,%1.4f)\n",
               x[0], y[0], x[N - 1], y[N - 1]);
    }
    free(x);
    free(y);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
