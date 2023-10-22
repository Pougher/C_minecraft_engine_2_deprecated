#ifndef ECS_H
#define ECS_H

#include <stdio.h>
#include <stdlib.h>

#include "../core/dynarray.h"

#include "../common/types.h"
#include "../common/log.h"

#include "ecs_type.h"
#include "ecs_type.h"
#include "entity.h"

#include "ecs_position.h"
#include "ecs_camera.h"

// macro to generate memory allocations for dynamic arrays containing entity
// components
#define ECS_COMPONENT(_name) manager->_name = dynarray_new(sizeof(ECS##_name))

// macro to free a dynarray of components
// NOTE: Does not free any references to data within the component objects,
// so some memory could be leaked if an object's self-allocated memory is
// not freed on the deletion of the dynamic array
#define ECS_COMPONENT_FREE(_name) dynarray_free(manager->_name)

// pastes in the code for generating an ecs component
#define ECS_ADD_COMPONENT(_name) ECS##_name _name;                      \
                                 ecs_##_name##_init(&_name);            \
                                 dynarray_push(manager->_name, &_name);

// simply removes the component through dynarray_delete. Also generates a case
// statement
#define ECS_DELETE(_match, _name) case _match: {                        \
                                     dynarray_reserve_delete(ecs->_name,\
                                         entity->components[i]);        \
                                  break; }

typedef struct {
    // the entity component lists that any entity can use
    DynArray *position;
    DynArray *camera;

    // the highest ID of the previously allocated entity
    u64 id;
} ECSManager;

// allocates a new ECS on the stack
ECSManager *ecs_new(void);

// creates an entity from a recipe
Entity *ecs_create_entity(ECSManager*, ECSType*, size_t);

// deletes an entity and all associated memory
void ecs_delete_entity(ECSManager*, Entity*);

// updates all of the components in the ECS
void ecs_update(ECSManager*);

// returns the ID of the component within the entity
u64 ecs_get_component_id(Entity*, u64);

// frees all data bound to the ECS including all memory allocated to entity
// components within the entity component list
void ecs_free(ECSManager*);

#endif
