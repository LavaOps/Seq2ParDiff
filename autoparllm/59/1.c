#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 1000
// Ejecutado con 8 hilos

int main() {
    double A[1000];
    double B[1000];
    int i;
    double suma;
    // Preguntar a Arturo pq al paralelizar este bucle tarda más que si lo dejas
    // sin paralelizar
    dummyMethod3();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 999; i += 1) {
        A[i] = 0.05;
        B[i] = 0.5;
    }
    dummyMethod4();
    suma = 0.0;
    /*Región indeopendiente pq depende del bucle anterior
        La operación de suma requiere de una reducción*/
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : suma)
    // #pragma rose_outline
    for (i = 0; i <= 999; i += 1) {
        suma = suma + A[i] * B[i];
    }
    dummyMethod2();
    printf("Suma %lf\n", suma);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
