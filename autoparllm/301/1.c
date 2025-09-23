#include <assert.h>
#include <float.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define DTYPE float
// define structures
typedef struct layer {
    char *name;
    struct layer *next;
    // basic
    float *input;
    float *output;
    int input_count;
    int ndim;
    int *input_shape;
    int *output_shape;
    int output_count;
    // pooling param
    int ksize;
    int pad;
    int stride;
} layer_t;
// define functions
layer_t *init_pooling(const char *name, const int ndim, const int *input_shape,
                      const int ksize, const int pad, const int stride);
void print_pooling(layer_t *l);
layer_t *forward_pooling(layer_t *l);
void print_pooling(layer_t *l);
void destroy_pooling(layer_t *l);

layer_t *init_pooling(const char *name, const int ndim, const int *input_shape,
                      const int ksize, const int pad, const int stride) {
    (((void)(sizeof(
         ((ndim > 0 && input_shape && ksize > 0 && pad >= 0 && stride > 0
               ? 1
               : 0))))),
     (({
         if (ndim > 0 && input_shape && ksize > 0 && pad >= 0 && stride > 0)
             ;
         else
             __assert_fail(
                 "ndim>0 && input_shape && ksize>0 && pad>=0 && stride>0",
                 "ysh329_OpenMP-101_pooling.c", 49, __PRETTY_FUNCTION__);
     })));
    layer_t *l = (calloc(1, sizeof(layer_t)));
    l->name = (calloc((strlen(name)), sizeof(char)));
    strcpy(l->name, name);
    l->next = ((void *)0);
    int input_count = 1;
    dummyMethod3();

#pragma omp parallel for reduction(* : input_count)
    // #pragma rose_outline
    for (int idx = 0; idx <= ndim - 1; idx += 1) {
        input_count *= input_shape[idx];
    }
    dummyMethod4();
    l->input = (calloc(input_count, sizeof(float)));
    l->input_count = input_count;
    l->ndim = ndim;
    l->input_shape = (calloc(ndim, ndim * sizeof(int)));
    l->output_shape = (calloc(ndim, ndim * sizeof(int)));
    memcpy((l->input_shape), input_shape, ndim * sizeof(int));
    memcpy((l->output_shape), input_shape, ndim * sizeof(int));
    l->output_shape[2] = (l->input_shape[2] + 2 * pad - ksize) / stride + 1;
    l->output_shape[3] = (l->input_shape[3] + 2 * pad - ksize) / stride + 1;
    l->output_count = 1;
    dummyMethod3();

    for (int idx = 0; idx <= ndim - 1; idx += 1) {
        l->output_count *= l->output_shape[idx];
    }
    dummyMethod4();
    l->output = (calloc((l->output_count), sizeof(float)));
    l->ksize = ksize;
    l->pad = pad;
    l->stride = stride;
    return l;
}

void print_pooling(layer_t *l) {
    (((void)(sizeof(((l ? 1 : 0))))), (({
         if (l)
             ;
         else
             __assert_fail("l", "ysh329_OpenMP-101_pooling.c", 90,
                           __PRETTY_FUNCTION__);
     })));
    printf("---- print_pooling ----\n");
    printf("l->name:%s\n", l->name);
    printf("l->input_shape:");
    dummyMethod3();
    for (int idx = 0; idx <= l->ndim - 1; idx += 1) {
        printf("%d ", l->input_shape[idx]);
    }
    dummyMethod4();
    printf("\n");
    printf("l->output_shape:");
    dummyMethod3();
    for (int idx = 0; idx <= l->ndim - 1; idx += 1) {
        printf("%d ", l->output_shape[idx]);
    }
    dummyMethod4();
    printf("\n");
    printf("l->input_count:%d\n", l->input_count);
    printf("l->output_count:%d\n", l->output_count);
    printf("l->ksize:%d\n", l->ksize);
    printf("l->pad:%d\n", l->pad);
    printf("l->stride:%d\n", l->stride);
    printf("\n");
    return;
}
// refer darknet implementation
#define OUT_IDX(n, c, h, w)                                                    \
    l->output[n * l->output_shape[1] * l->output_shape[2] *                    \
                  l->output_shape[3] +                                         \
              c * l->output_shape[2] * l->output_shape[3] +                    \
              h * l->output_shape[3] + w]
#define IN_IDX(n, c, h, w)                                                     \
    l->input[n * l->input_shape[1] * l->input_shape[2] * l->input_shape[3] +   \
             c * l->input_shape[2] * l->input_shape[3] +                       \
             h * l->input_shape[3] + w]

layer_t *forward_pooling(layer_t *l) {
    (((void)(sizeof(((l ? 1 : 0))))), (({
         if (l)
             ;
         else
             __assert_fail("l", "ysh329_OpenMP-101_pooling.c", 125,
                           __PRETTY_FUNCTION__);
     })));
    int h_offset = -l->pad;
    int w_offset = -l->pad;
    dummyMethod1();
    for (int b = 0; b <= l->output_shape[0] - 1; b += 1) {
        for (int k = 0; k <= l->output_shape[1] - 1; k += 1) {
            for (int i = 0; i <= l->output_shape[2] - 1; i += 1) {
                for (int j = 0; j <= l->output_shape[3] - 1; j += 1) {
                    int out_idx =
                        l->output[b * l->output_shape[1] * l->output_shape[2] *
                                      l->output_shape[3] +
                                  k * l->output_shape[2] * l->output_shape[3] +
                                  i * l->output_shape[3] + j];
                    int max_idx = -1;
                    float max = -3.40282346638528859811704183484516925e+38F;

                    for (int n = 0; n <= l->ksize - 1; n += 1) {
                        for (int m = 0; m <= l->ksize - 1; m += 1) {
                            int cur_h = i * l->stride + h_offset + n;
                            int cur_w = j * l->stride + w_offset + m;
                            int in_idx =
                                l->input[b * l->input_shape[1] *
                                             l->input_shape[2] *
                                             l->input_shape[3] +
                                         k * l->input_shape[2] *
                                             l->input_shape[3] +
                                         cur_h * l->input_shape[3] + cur_w];
                            int valid = cur_h >= 0 && cur_h < l->output[2] &&
                                        cur_w >= 0 && cur_w < l->output[3];
                            float val =
                                valid != 0
                                    ? l->input[in_idx]
                                    : -3.40282346638528859811704183484516925e+38F;
                            max = (val > max ? val : max);
                            max_idx = (val > max ? in_idx : max_idx);
                        }
                    }
                    l->output[out_idx] = max;
                    // l->indexes[out_idx] = max_idx; // record for backprop
                }
            }
        }
    }
    dummyMethod2();
    return l;
}

void destroy_pooling(layer_t *l) {
    (((void)(sizeof(
         ((l && l->input && l->output && l->input_shape && l->output_shape
               ? 1
               : 0))))),
     (({
         if (l && l->input && l->output && l->input_shape && l->output_shape)
             ;
         else
             __assert_fail("l && l->input && l->output && l->input_shape && "
                           "l->output_shape",
                           "ysh329_OpenMP-101_pooling.c", 172,
                           __PRETTY_FUNCTION__);
     })));
    if (l->input)
        free((l->input));
    l->input = ((void *)0);
    if (l->input_shape)
        free((l->input_shape));
    l->input_shape = ((void *)0);
    if (l->output)
        free((l->output));
    l->output = ((void *)0);
    if (l->output_shape)
        free((l->output_shape));
    l->output_shape = ((void *)0);
    if (l->next)
        free((l->next));
    l->next = ((void *)0);
    // TODO: loop free layer-wise
    if (l)
        free(l);
    l = ((void *)0);
    return;
}

int main(int argc, char *argv[]) {
    // init
    const char *name = "pooling_layer";
    const int ndim = 4;
    const int ksize = 2;
    const int pad = 1;
    const int stride = 2;
    int *input_shape = (calloc(ndim, sizeof(int)));
    input_shape[0] = 1;
    input_shape[1] = 3;
    input_shape[2] = 224;
    input_shape[3] = 224;
    layer_t *l = init_pooling(name, ndim, input_shape, ksize, pad, stride);
    print_pooling(l);
    // forward pooling
    l = forward_pooling(l);
    // free
    destroy_pooling(l);
    if (input_shape)
        free(input_shape);
    input_shape = ((void *)0);
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
