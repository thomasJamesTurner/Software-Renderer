#ifndef MATHS_H
#define MATHS_H

#include <stddef.h>
#include <stdbool.h>
//declares the diffent dataype sufixes so Vec_f32 and Vec_f64 are distict types that are remembered
#define DECLARE_TYPES(SUFFIX, T)                          \
    typedef struct { T *data; size_t len; }  vec_##SUFFIX; \
    typedef struct { T *data; size_t rows, cols; } mat_##SUFFIX;

DECLARE_TYPES(i32, int)
DECLARE_TYPES(f32, float)
DECLARE_TYPES(f64, double)

#define DECLARE_OPS(SUFFIX)                                                \
    vec_##SUFFIX vec_make_##SUFFIX(size_t len);                            \
    vec_##SUFFIX vec_add_##SUFFIX(vec_##SUFFIX a, vec_##SUFFIX b);         \
    mat_##SUFFIX matmul_##SUFFIX(mat_##SUFFIX a, mat_##SUFFIX b);

DECLARE_OPS(i32)
DECLARE_OPS(f32)
DECLARE_OPS(f64)

#endif // !MATHS_H
