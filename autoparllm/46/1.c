#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a[100][100];
int main() {
    int i, j;
    dummyMethod1();
    float car_foam = 1;
    for (i = 0; i < 100; i++)
#pragma omp parallel for reduction(* : car_foam)
        // #pragma rose_outline
        for (j = 0; j < 100; j++)
            car_foam *= a[i][j];
    printf("%f", car_foam);
    dummyMethod2();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }