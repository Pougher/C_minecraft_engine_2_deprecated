#ifndef ECS_BLOCK_BREAK_H
#define ECS_BLOCK_BREAK_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include <math.h>
#include <stdbool.h>

#include "ecs_camera.h"

#include "../block/block.h"

#include "../util/ray.h"
#include "../util/mouse_state.h"

#define BLOCK_REACH 5

typedef struct {
    // reference to the entity camera
    ECScamera *cam;

    // reference to the entity position
    vec3 *pos;

    // block coordinates of the intersection
    vec3 intersection;

    // if the player has raycast into a block
    bool intersect;
} ECSblockbreak;

// initializes block break component.
// NOTE: The camera and position attributes must be assigned when the entity is
// created
void ecs_blockbreak_init(ECSblockbreak*);

// ticks the block breaking test
void ecs_blockbreak_mouse_tick(ECSblockbreak*, MouseState*);

#endif
