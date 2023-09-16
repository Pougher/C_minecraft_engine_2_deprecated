#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "../core/mesh.h"

#define WORLD_X 4
#define WORLD_Y 4
#define WORLD_Z 4
#define WORLD_AREA WORLD_X * WORLD_Y * WORLD_Z

typedef struct {
    // the chunks that make up the world
    Chunk **chunks;
} World;

// creates a new world with a list of chunks which has a size that is controlled
// by the WORLD_X, Y and Z values
World *world_new(void);

// renders the world to the screen by drawing each chunk's mesh
void world_render(World*);

// frees all data allocated to the world (including chunks)
void world_free(World*);

#endif
