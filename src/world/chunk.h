#ifndef CHUNK_H
#define CHUNK_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../core/mesh.h"
#include "../block/block.h"
#include "../common/log.h"
#include "../render/uv.h"

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

#define CHUNK_X 32
#define CHUNK_Y 32
#define CHUNK_Z 32

#define TO_INDEX(x, y, z) z + CHUNK_Z * (y + CHUNK_Y * x)

typedef struct {
    // the mesh of the chunk, should be updated every time the data array is
    // changed
    Mesh *mesh;

    // The block data array, holds a list of blocks in 1 dimensional form. Each
    // index into the array has to be mathematically calculated
    BlockType *blocks;

    // the x location of the chunk
    int64_t x;

    // the y location of the chunk
    int64_t y;

    // the z location of the chunk
    int64_t z;
} Chunk;

// creates a new chunk at an x and y coordinate. Automatically allocates the
// chunk's internal mesh and block data
Chunk *chunk_new(int64_t, int64_t, int64_t);

// frees the chunk's mesh and internal block data
void chunk_free(Chunk*);

// computes the chunks mesh
void chunk_compute_mesh(Chunk*);

// gets a block from a chunk at an (x, y, z) coordinate
BlockType chunk_get_block(Chunk*, int, int, int);

#endif
