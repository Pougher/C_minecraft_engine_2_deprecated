#ifndef BLOCK_H
#define BLOCK_H

#include <stdbool.h>
#include <cglm/cglm.h>

#include "../render/uv.h"

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

#define NUM_BLOCKS 2

typedef enum {
    AIR         = 0,
    DIRT        = 1,
} BlockType;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD
} Direction;

typedef struct {
    // the id of the block
    BlockType id;

    // block transparency (the block will not be rendered)
    bool transparent;

    // a function to get the texture location of the block id
    TexUVi (*get_texture_location)(Direction);
} Block;

// macro to automatically generate block declarations
#define BLOCK_DECL(name)                \
    extern void name##_init(void); \
    name##_init();

// function to initialize an array of blocks
void block_init(void);

#endif
