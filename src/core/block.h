#ifndef BLOCK_H
#define BLOCK_H

#define BLOCK_FACE_0(x, y, z, uv) (float[30]) {             \
    0.0f + x, 0.0f + y, 0.0f + z, uv.u, uv.v,               \
    1.0f + x, 0.0f + y, 0.0f + z, uv.u + uv.w, uv.v,        \
    1.0f + x, 1.0f + y, 0.0f + z, uv.u + uv.w, uv.v + uv.h, \
    1.0f + x, 1.0f + y, 0.0f + z, uv.u + uv.w, uv.v + uv.h, \
    0.0f + x, 1.0f + y, 0.0f + z, uv.u, uv.v + uv.h,        \
    0.0f + x, 0.0f + y, 0.0f + z, uv.u, uv.v }

#define BLOCK_FACE_1(x, y, z, uv) (float[30]) {             \
    0.0f + x, 0.0f + y, 1.0f + z, uv.u, uv.v,               \
    1.0f + x, 0.0f + y, 1.0f + z, uv.u + uv.w, uv.v,        \
    1.0f + x, 1.0f + y, 1.0f + z, uv.u + uv.w, uv.v + uv.h, \
    1.0f + x, 1.0f + y, 1.0f + z, uv.u + uv.w, uv.v + uv.h, \
    0.0f + x, 1.0f + y, 1.0f + z, uv.u, uv.v + uv.h,        \
    0.0f + x, 0.0f + y, 1.0f + z, uv.u, uv.v }

#define BLOCK_FACE_2(x, y, z, uv) (float[30]) {             \
    0.0f + x, 1.0f + y, 1.0f + z, uv.u, uv.v,               \
    0.0f + x, 1.0f + y, 0.0f + z, uv.u + uv.w, uv.v,        \
    0.0f + x, 0.0f + y, 0.0f + z, uv.u + uv.w, uv.v + uv.h, \
    0.0f + x, 0.0f + y, 0.0f + z, uv.u + uv.w, uv.v + uv.h, \
    0.0f + x, 0.0f + y, 1.0f + z, uv.u, uv.v + uv.h,        \
    0.0f + x, 1.0f + y, 1.0f + z, uv.u, uv.v }

#define BLOCK_FACE_3(x, y, z, uv) (float[30]) {             \
    1.0f + x, 1.0f + y, 1.0f + z, uv.u, uv.v,               \
    1.0f + x, 1.0f + y, 0.0f + z, uv.u + uv.w, uv.v,        \
    1.0f + x, 0.0f + y, 0.0f + z, uv.u + uv.w, uv.v + uv.h, \
    1.0f + x, 0.0f + y, 0.0f + z, uv.u + uv.w, uv.v + uv.h, \
    1.0f + x, 0.0f + y, 1.0f + z, uv.u, uv.v + uv.h,        \
    1.0f + x, 1.0f + y, 1.0f + z, uv.u, uv.v }

#define BLOCK_FACE_4(x, y, z, uv) (float[30]) {             \
    0.0f + x, 0.0f + y, 0.0f + z, uv.u, uv.v,               \
    1.0f + x, 0.0f + y, 0.0f + z, uv.u + uv.w, uv.v,        \
    1.0f + x, 0.0f + y, 1.0f + z, uv.u + uv.w, uv.v + uv.h, \
    1.0f + x, 0.0f + y, 1.0f + z, uv.u + uv.w, uv.v + uv.h, \
    0.0f + x, 0.0f + y, 1.0f + z, uv.u, uv.v + uv.h,        \
    0.0f + x, 0.0f + y, 0.0f + z, uv.u, uv.v }

#define BLOCK_FACE_5(x, y, z, uv) (float[30]) {             \
    0.0f + x, 1.0f + y, 0.0f + z, uv.u, uv.v,               \
    1.0f + x, 1.0f + y, 0.0f + z, uv.u + uv.w, uv.v,        \
    1.0f + x, 1.0f + y, 1.0f + z, uv.u + uv.w, uv.v + uv.h, \
    1.0f + x, 1.0f + y, 1.0f + z, uv.u + uv.w, uv.v + uv.w, \
    0.0f + x, 1.0f + y, 1.0f + z, uv.u, uv.v + uv.h,        \
    0.0f + x, 1.0f + y, 0.0f + z, uv.u, uv.v }

typedef enum {
    AIR = 0,
    DIRT
} BlockType;

#endif
