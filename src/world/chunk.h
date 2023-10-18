#ifndef CHUNK_H
#define CHUNK_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../core/mesh.h"
#include "../block/block.h"
#include "../common/log.h"
#include "../common/noise.h"
#include "../common/types.h"

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#define CHUNK_X 32
#define CHUNK_Y 128
#define CHUNK_Z 32

#define CHUNK_OVERSCAN_X (CHUNK_X + 2)
#define CHUNK_OVERSCAN_Y (CHUNK_Y + 2)
#define CHUNK_OVERSCAN_Z (CHUNK_Z + 2)

#define TO_INDEX(x, y, z) z + CHUNK_Z * (y + CHUNK_Y * x)

#define BLOCK_UV_POS(dir, ind) \
    ind = state->blocks[chunk->blocks[i]].get_texture_location(dir);

#define TEST_ADJACENT(_test, _v, _r) \
    if (_test) { _v = _r; adjacent = true; }

typedef struct {
    // the solid mesh of the chunk, should be updated every time the data array
    // is changed. Only stores the data of solid blocks
    Mesh *solid_mesh;

    // the fluid mesh of the chunk. Holds all vertex information regarding
    // translucent geometry.
    Mesh *fluid_mesh;

    // The block data array, holds a list of blocks in 1 dimensional form. Each
    // index into the array has to be mathematically calculated
    BlockType *blocks;

    // the x location of the chunk
    i64 x;

    // the y location of the chunk
    i64 y;

    // the z location of the chunk
    i64 z;

    // the relative location of the chunk to the rest of the world
    i16 rx;
    i16 ry;
    i16 rz;
} Chunk;

// creates a new chunk at an x and y coordinate. Automatically allocates the
// chunk's internal mesh and block data
Chunk *chunk_new(i64, i64, i64);

// generates the chunk with simplex noise to create a realistic world
void chunk_generate(Chunk*);

// frees the chunk's mesh and internal block data
void chunk_free(Chunk*);

// computes the chunks mesh
void chunk_compute_mesh(Chunk*);

// gets a block from a chunk at an (x, y, z) coordinate
BlockType chunk_get_block(Chunk*, i32, i32, i32);

#endif
