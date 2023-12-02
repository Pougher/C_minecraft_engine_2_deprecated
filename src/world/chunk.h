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

#define CHUNK_OVERSCAN 1

#define CHUNK_OVERSCAN_X (CHUNK_X + 2 * CHUNK_OVERSCAN)
#define CHUNK_OVERSCAN_Y (CHUNK_Y + 2 * CHUNK_OVERSCAN)
#define CHUNK_OVERSCAN_Z (CHUNK_Z + 2 * CHUNK_OVERSCAN)

// the chance that a grass block has to generate a tree
#define CHUNK_TREE_CHANCE 70

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

    // the transparency mesh for transparent geometry (rendered last in the
    // pipeline)
    Mesh *transparent_mesh;

    // The block data array, holds a list of blocks in 1 dimensional form. Each
    // index into the array has to be mathematically calculated
    BlockType *blocks;

    // the coordinates of the chunk in world space
    i64 x, y, z;

    // the position of the chunk in chunk space
    i64 cx, cy, cz;

    // wether the chunk should be deleted
    bool unloadable;
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

// returns the index into the chunk's data of the block in the relative
// (x, y, z) coordinate
size_t chunk_compute_index(i32, i32, i32);

// gets a block from a chunk at an (x, y, z) coordinate while correcting for
// the overscan offset
BlockType chunk_get_block_offset(Chunk*, i32, i32, i32);

// sets a block in a chunk. If the block is being set outside of bounds, then
// the block will not be set.
void chunk_set_block(Chunk*, i32, i32, i32, BlockType);

#endif
