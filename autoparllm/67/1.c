#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 3
#define M 4

int main(int argc, const char *argv[]) {
    int *A;
    int *a;
    int *b;
    int alfa;
    int beta;
    int *r;
    int i;
    int j;
    A = ((int *)(malloc((4 * 3) * sizeof(int))));
    a = ((int *)(malloc(4 * sizeof(int))));
    b = ((int *)(malloc(3 * sizeof(int))));
    r = ((int *)(malloc(4 * sizeof(int))));
    srand((time(((void *)0))));
    alfa = 1 + rand() % 10;
    beta = 1 + rand() % 10;
    dummyMethod3();
    for (i = 0; i <= 3; i += 1) {
        for (j = 0; j <= 2; j += 1) {
            *(A + i * 3 + j) = rand() % 10;
            b[j] = j + 3;
        }
        a[i] = i + 1;
        r[i] = 0;
    }
    dummyMethod4();
    dummyMethod1();

#pragma omp parallel for private(i, j) firstprivate(beta)
    // #pragma rose_outline
    for (i = 0; i <= 3; i += 1) {
        for (j = 0; j <= 2; j += 1) {
            r[i] += alfa * A[i * 3 + j] * b[j];
        }
        r[i] += beta * a[i];
    }
    dummyMethod2();
    long p = 1;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(* : p)
    // #pragma rose_outline
    for (i = 0; i <= 3; i += 1) {
        p *= r[i];
    }
    dummyMethod2();
    printf("RISULTATI\nR[]:\n");
    dummyMethod3();
    for (i = 0; i <= 3; i += 1) {
        printf("%d\n", r[i]);
    }
    dummyMethod4();
    printf("P = %ld\n", p);
    printf("\n");
    /*
    printf("RISULTATI SEQUENZIALE\n");
    p=1;
    for(i=0;i<M;i++){
            r[i] = 0;
                    for(j=0;j<N;j++){
                            r[i] += alfa*A[i*N+j] * b[j];
                    }
                    r[i] += beta * a[i];
            }
            for(i=0;i<M;i++)
                            p *= r[i];
            for(i=0;i<M;i++)
                    printf("%d\n",r[i]);
            printf("%ld\n",p);
    */
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
