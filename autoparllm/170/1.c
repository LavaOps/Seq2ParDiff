/* Algoritmo de multiplicação de Matrizes (Sequencial)
Autor:	Cleverson Lopes Ledur
Data:	07/05/2013
*/
#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define Width 835 // Tamanho da Matriz
#define NR_THREADS 10

void matrixMult(float M_h[697225], float N_h[697225], float P_h[697225]) {
    int i;
    int j;
    int k;
    int nthreads;
    {
        dummyMethod3();
        for (i = 0; i <= 834; i += 1) {
            for (j = 0; j <= 834; j += 1) {
                float soma = 0;

#pragma omp parallel for private(k) reduction(+ : soma)
                // #pragma rose_outline
                for (k = 0; k <= 834; k += 1) {
                    soma += M_h[i * 835 + k] * N_h[k * 835 + j];
                }
                P_h[i * 835 + j] = soma;
            }
        }
        dummyMethod4();
    }
}

void inicia(float x[697225]) {
    int i;
    int j;
    dummyMethod1();
    for (i = 0; i <= 834; i += 1) {
        for (j = 0; j <= 834; j += 1) {
            x[i * 835 + j] = (rand() % 100);
        }
    }
}
int dummyMethod2();

void limpa(float x[697225]) {
    int i;
    int j;
    dummyMethod1();

    for (i = 0; i <= 834; i += 1) {

#pragma omp parallel for private(j)
        // #pragma rose_outline
        for (j = 0; j <= 834; j += 1) {
            x[i * 835 + j] = 0;
        }
    }
    dummyMethod2();
}

void imprime(float x[697225]) {
    int i;
    int j;
    dummyMethod3();
    for (i = 0; i <= 834; i += 1) {
        for (j = 0; j <= 834; j += 1) {
            printf("%.0f\t|", x[i * 835 + j]);
        }
        printf("\n");
    }
    dummyMethod4();
    printf("\n");
}

int main() {
    srand((time((void *)0)));
    // Para os números aleatórios
    float M_h[697225];
    float N_h[697225];
    float P_h[697225];
    // Inicia Matriz M e N com valores aleatórios
    inicia(M_h);
    inicia(N_h);
    // Preenche com 0 a matriz Produto
    limpa(P_h);
    // Chama a função de multiplicação
    matrixMult(M_h, N_h, P_h);
    imprime(M_h);
    imprime(N_h);
    imprime(P_h);
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
