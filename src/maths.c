
#include <stdlib.h>
#include "maths.h"
//the intention was to make a macro to make the datatypes and the functions
//that being said designing and debuging this is going to be a pain so im
//just ask ai to write it and im going to write some unit tests and pray :(
#define DEFINE_OPS(SUFFIX, T)                                                  \
                                                                               \
    vec_##SUFFIX vec_make_##SUFFIX(size_t len) {                               \
        vec_##SUFFIX v = { calloc(len, sizeof(T)), len };                      \
        if (!v.data) v.len = 0;                                                \
        return v;                                                              \
    }                                                                          \
                                                                               \
    /* returns {NULL,0} on length mismatch or allocation failure */            \
    vec_##SUFFIX vec_add_##SUFFIX(vec_##SUFFIX a, vec_##SUFFIX b) {            \
        if (a.len != b.len) return (vec_##SUFFIX){ NULL, 0 };                  \
        vec_##SUFFIX out = vec_make_##SUFFIX(a.len);                           \
        if (!out.data && a.len) return out;                                    \
        for (size_t i = 0; i < a.len; ++i) out.data[i] = a.data[i] + b.data[i];\
        return out;                                                            \
    }                                                                          \
                                                                               \
    mat_##SUFFIX matmul_##SUFFIX(mat_##SUFFIX a, mat_##SUFFIX b) {             \
        if (a.cols != b.rows) return (mat_##SUFFIX){ NULL, 0, 0 };             \
        mat_##SUFFIX out = { calloc(a.rows * b.cols, sizeof(T)),               \
                             a.rows, b.cols };                                 \
        if (!out.data) return (mat_##SUFFIX){ NULL, 0, 0 };                    \
        for (size_t i = 0; i < a.rows; ++i)                                    \
            for (size_t j = 0; j < b.cols; ++j) {                              \
                T sum = 0;                                                     \
                for (size_t k = 0; k < a.cols; ++k)                            \
                    sum += a.data[i*a.cols + k] * b.data[k*b.cols + j];        \
                out.data[i*b.cols + j] = sum;                                  \
            }                                                                  \
        return out;                                                            \
    }

DEFINE_OPS(i32, int)
DEFINE_OPS(f32, float)
DEFINE_OPS(f64, double)

#define vec_add(a, b) _Generic((a),   \
    vec_i32: vec_add_i32,             \
    vec_f32: vec_add_f32,             \
    vec_f64: vec_add_f64)(a, b)

#define matmul(a, b) _Generic((a),    \
    mat_i32: matmul_i32,              \
    mat_f32: matmul_f32,              \
    mat_f64: matmul_f64)(a, b)

#define free_data(x) free((x).data)
