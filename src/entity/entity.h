#ifndef ENTITY_H
#define ENTITY_H

#include "../core/dynarray.h"

#include "../common/types.h"

#include "ecs_type.h"
#include "ecs_position.h"
#include "ecs_camera.h"
#include "ecs_block_break.h"
#include "ecs_block_place.h"
#include "ecs_physics.h"
#include "ecs_player_controller.h"

// definition to define any entity component
#define ENTITY_COMPONENT_DEF(n) ECS##n *n

typedef struct Entity {
    // the ID of the entity (0-2^64)
    u64 id;

    // define each component
    ENTITY_COMPONENT_DEF(position);
    ENTITY_COMPONENT_DEF(camera);
    ENTITY_COMPONENT_DEF(blockplace);
    ENTITY_COMPONENT_DEF(blockbreak);
    ENTITY_COMPONENT_DEF(physics);
    ENTITY_COMPONENT_DEF(playercontroller);
} Entity;

#endif
