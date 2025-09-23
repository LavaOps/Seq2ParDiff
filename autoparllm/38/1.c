#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern
#ifdef __cplusplus
    "C"
#endif
    void
    abort(void);

unsigned long long int k = 16;

int main() {
    unsigned char a[144], b[144], c[144];
    int l;
    {
        int i;
        unsigned long long int j;
        dummyMethod1();
#pragma omp parallel for private(i)
        // #pragma rose_outline
        for (i = 0; i < 16; i++)
            a[i] = i;
        dummyMethod2();
        dummyMethod1();
        for (i = 0; i < 16; i++)
            a[i + 16] = i + 16;
        dummyMethod2();
        dummyMethod1();
        for (i = 0; i < 16; i++)
            a[i + 32] = i + 32;
        dummyMethod2();
        {
            dummyMethod3();
            for (i = 0; i < 16; i++)
                a[i + 48] = i + 48;
            dummyMethod4();
            dummyMethod3();
            for (i = 0; i < 16; i++)
                a[i + 64] = i + 64;
            dummyMethod4();
            dummyMethod3();
            for (i = 0; i < 16; i++)
                a[i + 80] = i + 80;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                a[j + 96] = j + 96;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                a[j + 112] = j + 112;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                a[j + 128] = j + 128;
            dummyMethod4();
        }
        for (i = 0; i < 144; ++i)
            printf("a[%d]=%d\n", i, a[i]);
        dummyMethod1();
        for (i = 0; i < 16; i++)
            b[i] = i;
        dummyMethod2();
        dummyMethod1();
        for (i = 0; i < 16; i++)
            b[i + 16] = i + 16;
        dummyMethod2();
        dummyMethod1();
        for (i = 0; i < 16; i++)
            b[i + 32] = i + 32;
        dummyMethod2();
        {
            dummyMethod3();
            for (i = 0; i < 16; i++)
                b[i + 48] = i + 48;
            dummyMethod4();
            dummyMethod3();
            for (i = 0; i < 16; i++)
                b[i + 64] = i + 64;
            dummyMethod4();
            dummyMethod3();
            for (i = 0; i < 16; i++)
                b[i + 80] = i + 80;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                b[j + 96] = j + 96;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                b[j + 112] = j + 112;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                b[j + 128] = j + 128;
            dummyMethod4();
        }
        for (i = 0; i < 144; ++i)
            printf("b[%d]=%d\n", i, b[i]);
        dummyMethod1();
        for (i = 0; i < 16; i++)
            c[i] = i;
        dummyMethod2();
        dummyMethod1();
        for (i = 0; i < 16; i++)
            c[i + 16] = i + 16;
        dummyMethod2();
        dummyMethod1();
        for (i = 0; i < 16; i++)
            c[i + 32] = i + 32;
        dummyMethod2();
        {
            dummyMethod3();
            for (i = 0; i < 16; i++)
                c[i + 48] = i + 48;
            dummyMethod4();
            dummyMethod3();
            for (i = 0; i < 16; i++)
                c[i + 64] = i + 64;
            dummyMethod4();
            dummyMethod3();
            for (i = 0; i < 16; i++)
                c[i + 80] = i + 80;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                c[j + 96] = j + 96;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                c[j + 112] = j + 112;
            dummyMethod4();
            dummyMethod3();
            for (j = 0; j < k; j++)
                c[j + 128] = j + 128;
            dummyMethod4();
        }
        for (i = 0; i < 144; ++i)
            printf("c[%d]=%d\n", i, c[i]);
    }
    dummyMethod3();
    for (l = 0; l < 144; ++l)
        if (a[l] != l || b[l] != l || c[l] != l)
            abort();
    dummyMethod4();
    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }