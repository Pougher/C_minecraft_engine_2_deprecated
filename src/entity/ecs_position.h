#ifndef ECS_POSITION_H
#define ECS_POSITION_H

#include "../common/types.h"

// component to hold the position of an entity.
typedef struct {
    // the position in 3D world space of the entity
    i64 x;
    i64 y;
    i64 z;
} ECSposition;

// initializes the values of a new position component
void ecs_position_init(ECSposition*);

#endif
