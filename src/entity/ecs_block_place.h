#ifndef ECS_BLOCK_PLACE_H
#define ECS_BLOCK_PLACE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include <math.h>
#include <stdbool.h>

#include "ecs_camera.h"
#include "ecs_defaults.h"

#include "../block/block.h"

#include "../util/ray.h"
#include "../util/mouse_state.h"

struct Entity;

typedef struct {
    // the current block ID that the player is placing
    BlockType id;
} ECSblockplace;

// initializes the block place component
void ecs_blockplace_init(ECSblockplace*);

void ecs_blockplace_tick(struct Entity*, ECSblockplace*);

// tick the block placing test on every mouse frame
void ecs_blockplace_mouse_tick(struct Entity*, ECSblockplace*, MouseState*);

#endif
