#ifndef ECS_H
#define ECS_H

#include <stdio.h>
#include <stdlib.h>

#include "../core/dynarray.h"

#include "../common/types.h"

#include "ecs_position.h"

// macro to generate memory allocations for dynamic arrays containing entity
// components
#define ECS_COMPONENT(_name) manager->_name = dynarray_new(sizeof(ECS##_name))

// macro to free a dynarray of components
// NOTE: Does not free any references to data within the component objects,
// so some memory could be leaked if an object's self-allocated memory is
// not freed on the deletion of the dynamic array
#define ECS_COMPONENT_FREE(_name) dynarray_free(manager->_name)

typedef struct {
    // the entity component lists that any entity can use
    DynArray *position;
} ECSManager;

// allocates a new ECS on the stack
ECSManager *ecs_new(void);

// frees all data bound to the ECS including all memory allocated to entity
// components within the entity component list
void ecs_free(ECSManager*);

#endif
