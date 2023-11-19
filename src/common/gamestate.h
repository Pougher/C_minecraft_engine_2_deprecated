#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stdio.h>
#include <stdlib.h>

#include <cglm/cglm.h>

#include "camera.h"
#include "log.h"

#include "../world/world.h"

#include "../render/grid_atlas.h"
#include "../render/shader.h"

#include "../block/block.h"

#include "../common/types.h"

#include "../entity/ecs.h"

struct GameState {
    // the player entity
    Entity *player;

    // world data
    World *world;

    // Global block texture atlas
    GridAtlas *block_atlas;

    // global shaders array
    Shader *shaders;

    // information about various block types
    Block blocks[NUM_BLOCKS];

    // the entity manager
    ECSManager *ecs;

    // the number of allocated shaders
    i32 num_shaders;

    // the time passed between two frames, helps keep track of timings
    float delta;
};

extern struct GameState *state;

// initializes a gamestate object
void gamestate_init(char*, char**, i32);

// frees all data allocated to the gamestate struct
void gamestate_free(void);

#endif
