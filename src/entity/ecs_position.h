#ifndef ECS_POSITION_H
#define ECS_POSITION_H

#include <cglm/cglm.h>

#include "../world/chunk.h"

#include "../common/types.h"

struct Entity;

// component to hold the position of an entity.
typedef struct {
    // the position in 3D world space of the entity
    vec3 pos;

    // the chunk coordinates of the entity
    // (READONLY. Modification will have no effect)
    i64 chunk_x;
    i64 chunk_y;
    i64 chunk_z;
} ECSposition;

// initializes the values of a new position component
void ecs_position_init(ECSposition*);

// called every game tick, updates the chunk coordinates value of an entity
void ecs_position_tick(struct Entity*, ECSposition*);

#endif
