#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#include "omp.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
int NB_WORDS = 10;
int STRING_MAX_SIZE = 20;
/* A function to generate random strings */

void gen_random(char *s, int len) {
    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
    dummyMethod3();
    for (int i = 0; i <= len - 1; i += 1) {
        s[i] = alphanum[(rand()) % (sizeof(alphanum) - 1)];
    }
    dummyMethod4();
    s[len] = 0;
}
/* A function to print arrays of strings */

void printArrayStrings(char **array) {
    dummyMethod3();
    for (int i = 0; i <= NB_WORDS - 1; i += 1) {
        printf("%s\n", array[i]);
    }
    dummyMethod4();
}
/* A function to print the counts */

void printArrayInt(int *count) {
    dummyMethod3();
    for (int i = 0; i <= 25; i += 1) {
        printf("%d ", count[i]);
    }
    dummyMethod4();
}
/* A function that maps a String to a count of characters */

void map1(char *c, int *count) {
    dummyMethod3();

#pragma omp parallel for
    // #pragma rose_outline
    for (int i = 0; i <= 25; i += 1) {
        count[i] = 0;
    }
    dummyMethod4();
    dummyMethod3();
    for (int i = 0; ((unsigned long)i) <= strlen((const char *)c) - 1; i += 1) {
        count[((int)c[i]) - 97]++;
    }
    dummyMethod4();
}

int main() {
    // init
    char *array[NB_WORDS];
    srand((time(((void *)0))));
    dummyMethod3();
    for (int i = 0; i <= NB_WORDS - 1; i += 1) {
        int strSize = 1 + rand() % STRING_MAX_SIZE;
        array[i] = ((char *)(malloc(strSize * sizeof(char))));
        gen_random(array[i], strSize);
    }
    dummyMethod4();
    printArrayStrings(array);
    // map (on a single word)
    int *count = (int *)(malloc(26 * sizeof(int)));
    map1(array[0], count);
    // printArrayInt(count);
    //  map (parallel)
    int **countMult = (int **)(malloc(NB_WORDS * sizeof(int *)));
    dummyMethod3();
    for (int i = 0; i <= NB_WORDS - 1; i += 1) {
        countMult[i] = ((int *)(malloc(26 * sizeof(int))));
    }
    dummyMethod4();
    int resReduce1[26] = {(0)};
    int resReduce2 = 0;
    for (int i = 0; i <= NB_WORDS - 1; i += 1) {
        for (int j = 0;
             ((unsigned long)j) <= strlen((const char *)array[i]) - 1; j += 1) {
            {
                map1(array[i], countMult[i]);
            }
        }

#pragma omp parallel for
        // #pragma rose_outline
        for (int x = 0; x <= 25; x += 1) {
            resReduce1[x] = resReduce1[x] + countMult[i][x];
        }
    }
    {

#pragma omp parallel for reduction(+ : resReduce2)
        // #pragma rose_outline
        for (int i = 0; i <= 25; i += 1) {
            resReduce2 += resReduce1[i];
        }
    }
    for (int i = 0; i <= NB_WORDS - 1; i += 1) {
        printf("\n");
        printArrayInt(countMult[i]);
    }
    printf("\nTotal number of occurences of each letter ");
    for (int i = 0; i <= 25; i += 1) {
        printf("%d ", resReduce1[i]);
    }
    printf("\nTotal number of characters in the text %d \n", resReduce2);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
