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
#define N 10
int main();
/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void GPU__correlation(DATA_TYPE *data, DATA_TYPE *mean, DATA_TYPE *stddev,
                      int xx[10]) {
    int i;
    int j;
    int cc[10] = {(0), (0), (0), (0), (0), (0), (0), (0), (0), (0)};
    // Determine mean of column vectors of input data matrix
    dummyMethod1();
    for (j = 0; j <= 9; j += 1) {
        mean[j] = (xx[j] + cc[j]);
        for (i = 0; i <= 9; i += 1) {
            data[i] = mean[j];
        }
    }
    dummyMethod2();
    dummyMethod3();
    for (j = 0; j <= 9; j += 1) {
        stddev[j] = 0.0;
        // printf("xx = %d \n", xx[j]);
        for (i = 0; i <= 9; i += 1) {
            stddev[j] += data[i] + mean[j];
        }
    }
    dummyMethod4();
    return;
}

int main() {
    double t_start;
    double t_end;
    DATA_TYPE *data;
    DATA_TYPE *mean;
    DATA_TYPE *stddev;
    int xx[10] = {(0), (1), (2), (3), (4), (5), (6), (7), (8), (9)};
    // 静态数组
    data = ((DATA_TYPE *)(malloc(10 * sizeof(DATA_TYPE))));
    mean = ((DATA_TYPE *)(malloc(10 * sizeof(DATA_TYPE))));
    stddev = ((DATA_TYPE *)(malloc(10 * sizeof(DATA_TYPE))));
    int m;
    dummyMethod3();

#pragma omp parallel for private(m)
    // #pragma rose_outline
    for (m = 0; m <= 9; m += 1) {
        // mean[i] = i;
        data[m] = m;
    }
    dummyMethod4();
    GPU__correlation(data, mean, stddev, xx);
    dummyMethod3();
    for (int i = 0; i <= 9; i += 1) {
        printf("mean: %f\n", mean[i]);
    }
    dummyMethod4();
    dummyMethod3();
    for (int i = 0; i <= 9; i += 1) {
        printf("data: %f\n", data[i]);
    }
    dummyMethod4();
    free(data);
    free(mean);
    free(stddev);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
