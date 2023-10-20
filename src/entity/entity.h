#ifndef ENTITY_H
#define ENTITY_H

#include "../core/dynarray.h"

#include "../common/types.h"


typedef struct {
    // the ID of the entity (0-2^64)
    u64 id;

    // the list of all component tags that can be accessed by the entity. Each
    // tag is made up of a 32 bit tag type and another 32 bit tag ID
    u64 *components;

    // the number of components that the entity has
    i32 components_num;
} Entity;

#endif
