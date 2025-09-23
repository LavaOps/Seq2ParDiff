#include "omp.h"
#include <omp.h>
#include <stdio.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    char str[10];
    char temp[20] = "files/";
    int i = 0;
    int length = 0;
    int count = 0;
    length = strlen(temp);
    dummyMethod1();

#pragma omp parallel for private(i)
    // #pragma rose_outline
    for (i = 0; i <= 4; i += 1) {
        temp[length + i] = 'c';
        //  printf("%d %d\n",i ,omp_get_thread_num());
    }
    dummyMethod2();
    temp[length + 5] = '\0';
    printf("%s %d\n", temp, i);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
