#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#else
#define omp_get_thread_num() 0
#define omp_get_num_threads() 1
#define omp_get_num_procs()                                                    \
    (system("cat /proc/cpuinfo | grep 'processor' | wc -l"))
#endif
// Size of vectors.
#ifndef N
#define N 4096
#endif
// Entrada e saida.
#define DATA_TYPE double
double h_a[4096];
double h_b[4096];
double h_c[4096];

void init_array() {
    fprintf(stdout, "Inicializando os arrays.\n");
    int i;
    int number_of_threads = 4;
    dummyMethod1();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 4095; i += 1) {
        h_a[i] = 0.5;
        h_b[i] = 0.5;
    }
    dummyMethod2();
}

void print_array() {
    int i;
    fprintf(stdout, "Thread [%02d]: Imprimindo o array de resultados:\n", 0);
    dummyMethod3();
    for (i = 0; i <= 4095; i += 1) {
        fprintf(stdout, "Thread [%02d]: h_c[%07d]: %f\n", 0, i, h_c[i]);
    }
    dummyMethod4();
}

void check_result() {
    // Soma dos elementos do array C e divide por N, o valor deve ser igual a 1.
    int i;
    double sum = 0;
    fprintf(stdout, "Thread [%02d]: Verificando o resultado.\n", 0);
    dummyMethod3();

#pragma omp parallel for private(i) reduction(+ : sum)
    // #pragma rose_outline
    for (i = 0; i <= 4095; i += 1) {
        sum += h_c[i];
    }
    dummyMethod4();
    fprintf(stdout, "Thread [%02d]: Resultado Final: (%f, %f)\n", 0, sum,
            (double)(sum / ((double)4096)));
}

int main() {
    int i;
    init_array();
    int number_of_threads = 4;
    dummyMethod1();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 4095; i += 1) {
        h_c[i] = h_a[i] + h_b[i];
    }
    dummyMethod2();
    // print_array();
    check_result();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
