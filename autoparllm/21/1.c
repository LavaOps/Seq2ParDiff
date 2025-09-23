#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char **argv) {

    float height[1000];
    float width[1000];
    float cost_of_paint[1000];
    float area, price_per_gallon = 20.00, coverage = 20.5;
    int index;

    dummyMethod1();
#pragma omp parallel for private(index)
    // #pragma rose_outline
    for (index = 0; index < 1000; index++) {
        area = height[index] * width[index];
        cost_of_paint[index] = area * price_per_gallon / coverage;
    }
    for (index = 0; index < 1000; index++) {
        printf("cost_of_paint[%d]=%f\n", index, cost_of_paint[index]);
    }
    dummyMethod2();
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }