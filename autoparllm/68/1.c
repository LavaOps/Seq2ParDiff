#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/*SOMMA DEGLI ELEMENTI PARI DI UNA MATRICE (MATRICE CONSIDERATA COME ARRAY RIGA,
 * QUINDI 0,2,4,ecc..) */

int main(int argc, const char *argv[]) {
    int *mat;
    int N = 8;
    int i;
    int j;
    int pari = 0;
    int sumTOT = 0;
    ;
    mat = ((int *)(malloc((N * N) * sizeof(int))));
    dummyMethod3();

#pragma omp parallel for private(i, j)
    // #pragma rose_outline
    for (i = 0; i <= N - 1; i += 1) {
        for (j = 0; j <= N - 1; j += 1) {
            *(mat + i * N + j) = i + j + 1;
        }
    }
    dummyMethod4();
    dummyMethod1();

#pragma omp parallel for private(pari, i, j) reduction(+ : sumTOT)             \
    firstprivate(N)
    // #pragma rose_outline
    for (i = 0; i <= N - 1; i += 1) {
        for (j = 0; j <= N - 1; j += 1) {
            if (pari % 2 == 0)
                sumTOT += *(mat + i * N + j);
            pari++;
        }
    }
    dummyMethod2();
    printf("%d\n", sumTOT);
    /* SEQUENZIALE
            sumTOT =0;
            pari = 0;
            for(i=0;i<N;i++){
                            for(j=0;j<N;j++){
                                    if((pari %2) ==0 )
                                            sumTOT += *(mat+i*N+j);
                                            pari++;
                            }
                    }
            */
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
