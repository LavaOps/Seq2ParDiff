// C program for implementation of Bubble sort
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
// bubble sort

void bubbleSort(int arr[], int n) {
    int j = 0;
    int i = 0;
    int first;
    dummyMethod1();
    for (i = 0; i <= n - 1 - 1; i += 1) {
        first = i % 2;
        for (j = first; j <= n - 1 - 1; j += 1) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    dummyMethod2();
}
// Verify if the array is in ascending order

_Bool isArraySorted(int arr[], int size) {
    _Bool result = 1;
    dummyMethod3();

#pragma omp parallel for firstprivate(size)
    // #pragma rose_outline
    for (int i = 0; i <= size - 1 - 1; i += 1) {
        if (arr[i] > arr[i + 1])
            result = 0;
    }
    dummyMethod4();
    return result;
}
// Driver program to test above functions

int main() {
    int i;
    int n = 10000;
    int *arr = (int *)(malloc(n * sizeof(int)));
    dummyMethod1();
    for (i = 0; i <= n - 1; i += 1) {
        arr[i] = rand() % n;
    }
    dummyMethod2();
    bubbleSort(arr, n);
    printf("Is array sorted?: \n");
    fputs((isArraySorted(arr, n) ? "true\n" : "false\n"), stdout);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
