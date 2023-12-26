#ifndef ECS_BLOCK_BREAK_H
#define ECS_BLOCK_BREAK_H

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
    u8 empty;
} ECSblockbreak;

// initializes block break component.
// NOTE: The camera and position attributes must be assigned when the entity is
// created
void ecs_blockbreak_init(ECSblockbreak*);

// ticks the block breaking test
void ecs_blockbreak_mouse_tick(struct Entity*, ECSblockbreak*, MouseState*);

#endif
