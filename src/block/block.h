#ifndef BLOCK_H
#define BLOCK_H

#include <stdbool.h>
#include <cglm/cglm.h>

// 16x16 pixel blocks
#define BLOCK_SIZE 16

#define BLOCK_FACE_0(x, y, z, uv, i) (float[36]) {                  \
    0.0f + x, 0.0f + y, 0.0f + z, uv[0], uv[1], i,                  \
    1.0f + x, 0.0f + y, 0.0f + z, uv[0] + uv[2], uv[1], i,          \
    1.0f + x, 1.0f + y, 0.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    1.0f + x, 1.0f + y, 0.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    0.0f + x, 1.0f + y, 0.0f + z, uv[0], uv[1] + uv[3], i,          \
    0.0f + x, 0.0f + y, 0.0f + z, uv[0], uv[1], i }

#define BLOCK_FACE_1(x, y, z, uv, i) (float[36]) {                  \
    0.0f + x, 0.0f + y, 1.0f + z, uv[0], uv[1], i,                  \
    1.0f + x, 0.0f + y, 1.0f + z, uv[0] + uv[2], uv[1], i,          \
    1.0f + x, 1.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    1.0f + x, 1.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    0.0f + x, 1.0f + y, 1.0f + z, uv[0], uv[1] + uv[3], i,          \
    0.0f + x, 0.0f + y, 1.0f + z, uv[0], uv[1], i }

#define BLOCK_FACE_2(x, y, z, uv, i) (float[36]) {                  \
    0.0f + x, 1.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    0.0f + x, 1.0f + y, 0.0f + z, uv[0], uv[1] + uv[3], i,          \
    0.0f + x, 0.0f + y, 0.0f + z, uv[0], uv[1], i,                  \
    0.0f + x, 0.0f + y, 0.0f + z, uv[0], uv[1], i,                  \
    0.0f + x, 0.0f + y, 1.0f + z, uv[0] + uv[2], uv[1], i,          \
    0.0f + x, 1.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i }

#define BLOCK_FACE_3(x, y, z, uv, i) (float[36]) {                  \
    1.0f + x, 1.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    1.0f + x, 1.0f + y, 0.0f + z, uv[0], uv[1] + uv[3], i,          \
    1.0f + x, 0.0f + y, 0.0f + z, uv[0], uv[1], i,                  \
    1.0f + x, 0.0f + y, 0.0f + z, uv[0], uv[1], i,                  \
    1.0f + x, 0.0f + y, 1.0f + z, uv[0] + uv[2], uv[1], i,          \
    1.0f + x, 1.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i }

#define BLOCK_FACE_4(x, y, z, uv, i) (float[36]) {                  \
    0.0f + x, 0.0f + y, 0.0f + z, uv[0], uv[1], i,                  \
    1.0f + x, 0.0f + y, 0.0f + z, uv[0] + uv[2], uv[1], i,          \
    1.0f + x, 0.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    1.0f + x, 0.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    0.0f + x, 0.0f + y, 1.0f + z, uv[0], uv[1] + uv[3], i,          \
    0.0f + x, 0.0f + y, 0.0f + z, uv[0], uv[1], i }

#define BLOCK_FACE_5(x, y, z, uv, i) (float[36]) {                  \
    0.0f + x, 1.0f + y, 0.0f + z, uv[0], uv[1], i,                  \
    1.0f + x, 1.0f + y, 0.0f + z, uv[0] + uv[2], uv[1], i,          \
    1.0f + x, 1.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[3], i,  \
    1.0f + x, 1.0f + y, 1.0f + z, uv[0] + uv[2], uv[1] + uv[2], i,  \
    0.0f + x, 1.0f + y, 1.0f + z, uv[0], uv[1] + uv[3], i,          \
    0.0f + x, 1.0f + y, 0.0f + z, uv[0], uv[1], i}

#define NUM_BLOCKS 5

typedef enum {
    AIR         = 0,
    DIRT        = 1,
    GRASS       = 2,
    STONE       = 3,
    BEDROCK     = 4,
} BlockType;

typedef enum {
    UP          = 0,
    DOWN        = 1,
    LEFT        = 2,
    RIGHT       = 3,
    FORWARD     = 4,
    BACKWARD    = 5
} Direction;

typedef struct {
    // the id of the block
    BlockType id;

    // block transparency (the block will not be rendered)
    bool transparent;

    // a function to get the texture location of the block id
    int (*get_texture_location)(Direction);
} Block;

// macro to automatically generate block declarations
#define BLOCK_DECL(name)           \
    extern void name##_init(void); \
    name##_init()

// function to initialize an array of blocks
void block_init(void);

#endif
