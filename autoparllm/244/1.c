/*
   matmul.c : Matrix Multiplication with tiling for openmp4 example
*/
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define BLOCK_SIZE 16
/*
  #define BLOCK_SIZE 32
*/
#define NSECPERSEC 1000000000L
typedef struct {
    int width;
    int height;
    int stride;
    int hpad;
    float *elements;
} Matrix;
/* Correctly extract the number of nanoseconds from the two time structures */

long get_nanosecs(struct timespec start_time, struct timespec end_time) {
    long nanosecs;
    if (end_time.tv_nsec - start_time.tv_nsec < 0)
        nanosecs = (((long)end_time.tv_sec) - ((long)start_time.tv_sec) - 1) *
                       1000000000L +
                   (1000000000L + ((long)end_time.tv_nsec) -
                    ((long)start_time.tv_nsec));
    else
        nanosecs = (((long)end_time.tv_sec) - ((long)start_time.tv_sec)) *
                       1000000000L +
                   (((long)end_time.tv_nsec) - ((long)start_time.tv_nsec));
    return nanosecs;
}
void simple_sgemm_tt(const int M, const int N, const int K, const float alpha,
                     const float *A, const int LDA, const float *B,
                     const int LDB, const float beta, float *C, const int LDC);
void simple_sgemm_tn(const int M, const int N, const int K, const float alpha,
                     const float *A, const int LDA, const float *B,
                     const int LDB, const float beta, float *C, const int LDC);
void tiled_sgemm_tt(const int M, const int N, const int K, const float alpha,
                    const float *A, const int LDA, const float *B,
                    const int LDB, const float beta, float *C, const int LDC);

int verify(float *v_res, float *v_ref, int len) {
    int passed = 1;
    int i;
    dummyMethod3();
    for (i = 0; i <= len - 1; i += 1) {
        printf("v_res[%d]=%f, v_ref[%d]=%f\n", i, v_res[i], i, v_ref[i]);
    }
    fflush(stdout);
    for (i = 0; i <= len - 1; i += 1) {
        if (fabs((v_res[i] - v_ref[i])) > 0.001 * v_ref[i]) {
            __builtin_abort();
        }
    }
    dummyMethod4();
    return passed;
}

int main(int argc, char *argv[]) {
    Matrix A;
    Matrix B;
    Matrix Bt;
    Matrix C;
    Matrix Cref;
    int a1;
    int a2;
    int a3;
    int i;
    int j;
    struct timespec start_time1;
    struct timespec end_time1;
    struct timespec start_time2;
    struct timespec end_time2;
    long nanosecs;
    long total_ops;
    float gflopsTiled;
    float gflopsCPU;
    a1 = 35;
    a2 = 28;
    a3 = 47;
    A.height = a1;
    A.width = a2;
    A.stride = ((A.width - 1) / 16 + 1) * 16;
    A.hpad = ((A.height - 1) / 16 + 1) * 16;
    A.elements = ((float *)(malloc((A.stride * A.hpad) * sizeof(float))));
    B.height = a2;
    B.width = a3;
    B.stride = ((B.width - 1) / 16 + 1) * 16;
    B.hpad = ((B.height - 1) / 16 + 1) * 16;
    B.elements = ((float *)(malloc((B.stride * B.hpad) * sizeof(float))));
    /* Bt is same as B but stored in column-major order */
    Bt.height = B.height;
    Bt.width = B.width;
    Bt.stride = B.stride;
    Bt.hpad = B.hpad;
    Bt.elements = ((float *)(malloc((Bt.stride * Bt.hpad) * sizeof(float))));
    C.height = a1;
    C.width = a3;
    C.stride = ((C.width - 1) / 16 + 1) * 16;
    C.hpad = ((C.height - 1) / 16 + 1) * 16;
    C.elements = ((float *)(malloc((C.stride * C.hpad) * sizeof(float))));
    Cref.height = a1;
    Cref.width = a3;
    Cref.stride = ((Cref.width - 1) / 16 + 1) * 16;
    Cref.hpad = ((Cref.height - 1) / 16 + 1) * 16;
    Cref.elements =
        ((float *)(malloc((Cref.stride * Cref.hpad) * sizeof(float))));
    dummyMethod3();
    for (i = 0; i <= A.hpad - 1; i += 1) {
        for (j = 0; j <= A.stride - 1; j += 1) {
            if (j < A.width && i < A.height) {
                A.elements[i * A.stride + j] = (i % 3);
            } else {
                A.elements[i * A.stride + j] = 0.0;
            }
        }
    }
    dummyMethod4();
    /*  Initialize B and Bt */
    dummyMethod3();
    for (i = 0; i <= B.hpad - 1; i += 1) {
        for (j = 0; j <= B.stride - 1; j += 1) {
            if (j < B.width && i < B.height) {
                B.elements[i * B.stride + j] = (j % 2);
                Bt.elements[j * Bt.stride + i] = B.elements[i * B.stride + j];
            } else {
                B.elements[i * B.stride + j] = 0.0;
                Bt.elements[j * Bt.stride + i] = 0.0;
            }
        }
    }
    dummyMethod4();
    /* zero C, and Cref */
    dummyMethod3();
    for (i = 0; i <= C.hpad - 1; i += 1) {
        for (j = 0; j <= C.stride - 1; j += 1) {
            C.elements[i * C.stride + j] = 0.0;
            Cref.elements[i * Cref.stride + j] = 0.0;
        }
    }
    dummyMethod4();
    simple_sgemm_tt(A.height, B.width, B.height, 1.0, A.elements, A.stride,
                    B.elements, B.stride, 1.0, Cref.elements, Cref.stride);
    tiled_sgemm_tt(A.height, B.width, B.height, 1.0, A.elements, A.stride,
                   B.elements, B.stride, 1.0, C.elements, C.stride);
    verify(C.elements, Cref.elements, C.height * C.stride);
    return 0;
}

void simple_sgemm_tt(const int M, const int N, const int K, const float alpha,
                     const float *A, const int LDA, const float *B,
                     const int LDB, const float beta, float *C, const int LDC) {
    /*  A,B, and C  are in row-major order */
    int c_row;
    int c_col;
    int inner;
    float sum;
    dummyMethod3();
    for (c_col = 0; c_col <= N - 1; c_col += 1) {
        for (c_row = 0; c_row <= M - 1; c_row += 1) {
            sum = 0.0;

#pragma omp parallel for private(inner) reduction(+ : sum)                     \
    firstprivate(LDA, LDB)
            // #pragma rose_outline
            for (inner = 0; inner <= K - 1; inner += 1) {
                sum += A[c_row * LDA + inner] * B[inner * LDB + c_col];
            }
            C[c_row * LDC + c_col] =
                alpha * sum + beta * C[c_row * LDC + c_col];
        }
    }
    dummyMethod4();
}
/***************************
   tiled_sgemm_tt:  Tiled matrix multiplication:
***************************/

void tiled_sgemm_tt(const int M, const int N, const int K, const float alpha,
                    const float *A, const int LDA, const float *B,
                    const int LDB, const float beta, float *C, const int LDC) {
    for (int C_row_start = 0; C_row_start <= M - 1; C_row_start += 16) {
        for (int C_col_start = 0; C_col_start <= N - 1; C_col_start += 16) {
            // We now have M/BLOCK_SIZE * N/BLOCK_SIZE teams =
            // (M*N)/(BLOCK_SIZE*BLOCK_SIZE) The grid global dimensions are
            // M,N,1 The grid local dimensions are BLOCK_SIZE,BLOCK_SIZE,1
            // -------------------------------------------------------------------
            //      The rest of this code forms the HSAIL kernel with the
            //      pairs of "paralell for collapse(2)" loops repalced with a
            //      barrier. The kernel initializes these values C_row_start =
            //      get_group_id(0) * BLOCK_SIZE C_col_start = get_group_id(1) *
            //      BLOCK_SIZE row=get_local_id(0) col=get_local_id(1)
            // -------------------------------------------------------------------
            //       Each team has a local copy of these mini matrices
            float As[16][16];
            float Bs[16][16];
            float Cs[16][16];
            int C_row;
            int C_col;
            /* Zero Cs for this BLOCK */
            // - - - - - - - - - - - - - - - - - - - -
            // REPLACE NEXT THREE LINES WITH A BARRIER
            dummyMethod1();

#pragma omp parallel for
            // #pragma rose_outline
            for (int row = 0; row <= 15; row += 1) {
                for (int col = 0; col <= 15; col += 1) {
                    Cs[row][col] = 0.0;
                }
            }
            dummyMethod2();
            // This kblock loop is run on the master thread of each team
            for (int kblock = 0; kblock <= K - 1; kblock += 16) {
                // Copy global memory values to local memory
                // - - - - - - - - - - - - - - - - - - - -
                // REPLACE NEXT THREE LINES WITH A BARRIER
                dummyMethod1();

                for (int row = 0; row <= 15; row += 1) {

                    for (int col = 0; col <= 15; col += 1) {
                        // END BARRIER
                        // - - - - - - - - - - - - - - - - - - - -
                        C_row = C_row_start + row;
                        C_col = C_col_start + col;
                        if (C_row < M && kblock + col < K)
                            As[row][col] = A[C_row * LDA + kblock + col];
                        else
                            As[row][col] = 0;
                        if (kblock + row < K && C_col < N)
                            Bs[row][col] = B[(kblock + row) * LDB + C_col];
                        else
                            Bs[row][col] = 0;
                    }
                }
                dummyMethod2();
                // Calculate Cs <- Sum(As X Bs) across all kblocks
                // - - - - - - - - - - - - - - - - - - - -
                // REPLACE NEXT THREE LINES WITH A BARRIER
                dummyMethod1();

                for (int row = 0; row <= 15; row += 1) {

#pragma omp parallel for
                    // #pragma rose_outline
                    for (int col = 0; col <= 15; col += 1) {
                        // END BARRIER
                        // - - - - - - - - - - - - - - - - - - - -
                        for (int e = 0; e <= 15; e += 1) {
                            Cs[row][col] += As[row][e] * Bs[e][col];
                        }
                    }
                }
                dummyMethod2();
                /* End for kblock .. */
            }
            // Scale Update actual C from Cs
            // - - - - - - - - - - - - - - - - - - - -
            // REPLACE NEXT THREE LINES WITH A BARRIER
            dummyMethod1();
            for (int row = 0; row <= 15; row += 1) {
                for (int col = 0; col <= 15; col += 1) {
                    // END BARRIER
                    // - - - - - - - - - - - - - - - - - - - -
                    C_row = C_row_start + row;
                    C_col = C_col_start + col;
                    if (C_row < M && C_col < N) {
                        C[C_row * LDC + C_col] = alpha * Cs[row][col] +
                                                 beta * C[C_row * LDC + C_col];
                    }
                }
            }
            dummyMethod2();
            // -------------------------------------------------------------------
            // This is the end of the kernel
        }
    }
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
