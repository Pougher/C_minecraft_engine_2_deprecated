#ifndef ENTITY_H
#define ENTITY_H

#include "../core/dynarray.h"

#include "../common/types.h"

#include "ecs_type.h"

typedef struct {
    // the ID of the entity (0-2^64)
    u64 id;

    // list of tag values that each entity can access
    u64 components[TOTAL_COMPONENTS];
} Entity;

#endif
