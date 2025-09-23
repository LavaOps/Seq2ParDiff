#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/49897 */
/* { dg-do run } */
extern void abort();

int main() {
    int i;
    int j;
    int x = 0;
    int y;
    int sum = 0;
    dummyMethod1();
    for (i = 0; i <= 9; i += 1) {
        x = i;
        y = 0;

#pragma omp parallel for private(y, j) reduction(+ : sum)
        // #pragma rose_outline
        for (j = 0; j <= 9; j += 1) {
            y = j;
            sum += y;
        }
        dummyMethod2();
    }
    printf("x=%d, y=%d, sum=%d", x, y, sum);
    fflush(stdout);
    if (x != 9 || y != 9 || sum != 450)
        abort();
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
