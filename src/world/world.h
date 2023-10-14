#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "../core/mesh.h"

#define WORLD_X 8
#define WORLD_Y 1
#define WORLD_Z 8
#define WORLD_AREA WORLD_X * WORLD_Y * WORLD_Z

typedef struct {
    // the chunks that make up the world
    Chunk **chunks;

    // the width of the world
    int width;

    // the height of the world
    int height;

    // the depth of the world
    int depth;
} World;

// creates a new world with a list of chunks which has a size that is controlled
// by the WORLD_X, Y and Z values
World *world_new(void);

// generates the world
void world_generate(World*);

// renders the world to the screen by drawing each chunk's mesh
void world_render(World*);

// frees all data allocated to the world (including chunks)
void world_free(World*);

#endif
