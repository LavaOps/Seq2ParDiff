#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PC da PUC
 * Programa paralelizado
 *
 *Teste1
 *real	0m0.463s
 *user	0m1.800s
 *sys	0m0.004s
 *
 *Teste2
 *real	0m0.463s
 *user	0m1.803s
 *sys	0m0.000s
 *
 *Teste3
 *real	0m0.469s
 *user	0m1.803s
 *sys	0m0.004s
 *
 *Teste4
 *real	0m0.465s
 *user	0m1.808s
 *sys	0m0.000s
 *
 * Programa sequencial
 *
 *Teste1
 *real	0m1.448s
 *user	0m1.442s
 *sys	0m0.004s
 *
 *Teste2
 *real	0m1.448s
 *user	0m1.434s
 *sys	0m0.012s
 *
 *Teste3
 *real	0m1.466s
 *user	0m1.462s
 *sys	0m0.000s
 *
 *Teste4
 *real	0m1.459s
 *user	0m1.449s
 *sys	0m0.008s
 *
 */
// Meu PC:
//  Linux version 5.13.12-arch1-1 (linux@archlinux) (gcc (GCC) 11.1.0
//  CPU: Intel i7-7700 (8) @ 4.200GHz
//
//  Paralelizado
//  101,36s user 2,77s system 432% cpu 24,073 total
//
//  Não paralelizado
//  63,21s user 0,03s system 99% cpu 1:03,36 total

void mm(double *a, double *b, double *c, int width) {
    dummyMethod1();

    for (int i = 0; i <= width - 1; i += 1) {

        for (int j = 0; j <= width - 1; j += 1) {
            double sum = 0;

#pragma omp parallel for reduction(+ : sum)
            // #pragma rose_outline
            for (int k = 0; k <= width - 1; k += 1) {
                double x = a[i * width + k];
                double y = b[k * width + j];
                sum += x * y;
            }
            c[i * width + j] = sum;
        }
    }
    dummyMethod2();
}

int main() {
    int width = 500;
    double *a = (double *)(malloc((width * width) * sizeof(double)));
    double *b = (double *)(malloc((width * width) * sizeof(double)));
    double *c = (double *)(malloc((width * width) * sizeof(double)));
    dummyMethod1();

    for (int i = 0; i <= width - 1; i += 1) {

#pragma omp parallel for
        // #pragma rose_outline
        for (int j = 0; j <= width - 1; j += 1) {
            a[i * width + j] = i;
            b[i * width + j] = j;
            c[i * width + j] = 0;
        }
    }
    dummyMethod2();
    mm(a, b, c, width);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < width; j++) {
            printf("c[%d]=%f\n", i * width + j, c[i * width + j]);
        }
    }
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
