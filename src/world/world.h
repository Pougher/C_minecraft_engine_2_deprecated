#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"

#include "../core/mesh.h"
#include "../core/dynarray.h"

#include "../common/types.h"

#include "../entity/entity.h"
#include "../entity/ecs.h"

#define WORLD_X 8
#define WORLD_Y 1
#define WORLD_Z 8
#define WORLD_AREA WORLD_X * WORLD_Y * WORLD_Z

typedef struct {
    // the chunks that make up the world
    Chunk **chunks;

    // the width of the world
    i32 width;

    // the height of the world
    i32 height;

    // the depth of the world
    i32 depth;

    // the coordinates of the central chunk
    i64 centre[3];

    // the component storing the players current position in the world along
    // with chunk coordinates
    ECSposition *player_pos;
} World;

// creates a new world with a list of chunks which has a size that is controlled
// by the WORLD_X, Y and Z values
World *world_new(void);

// generates the world
void world_generate(World*);

// renders the world to the screen by drawing each chunk's mesh
void world_render(World*);

// updates the world based on the position of the player
void world_update(World*);

// frees all data allocated to the world (including chunks)
void world_free(World*);

#endif
