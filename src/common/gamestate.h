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

struct GameState {
    // the camera for the player
    Camera *player_camera;

    // world data
    World *world;

    // Global block texture atlas
    GridAtlas *block_atlas;

    // global shaders array
    Shader *shaders;

    // the number of allocated shaders
    i32 num_shaders;

    // information about various block types
    Block blocks[NUM_BLOCKS];
};

extern struct GameState *state;

// initializes a gamestate object
void gamestate_init(char*, char**, i32);

// frees all data allocated to the gamestate struct
void gamestate_free(void);

#endif
