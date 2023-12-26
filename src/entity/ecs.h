#ifndef ECS_H
#define ECS_H

#include <stdio.h>
#include <stdlib.h>

#include "../core/dynarray.h"

#include "../util/mouse_state.h"

#include "../common/types.h"
#include "../common/log.h"

#include "ecs_type.h"
#include "ecs_type.h"
#include "entity.h"

#include "ecs_position.h"
#include "ecs_camera.h"
#include "ecs_block_break.h"
#include "ecs_block_place.h"
#include "ecs_physics.h"
#include "ecs_player_controller.h"

// macro to generate memory allocations for dynamic arrays containing entity
// components
#define ECS_COMPONENT(_name) manager->_name = dynarray_new(sizeof(ECS##_name))

// macro to free a dynarray of components
// NOTE: Does not free any references to data within the component objects,
// so some memory could be leaked if an object's self-allocated memory is
// not freed on the deletion of the dynamic array
#define ECS_COMPONENT_FREE(_name) free(entity->_name);

// pastes in the code for generating an ecs component
#define ECS_ADD_COMPONENT(_name) ECS##_name _name;                      \
                                 ecs_##_name##_init(&_name);            \
                                 dynarray_push(manager->_name, &_name);

// simply removes the component through dynarray_delete. Also generates a case
// statement
#define ECS_DELETE(_name) \
    if (entity->_name != NULL) free(entity->_name);
// quick and dirty macro for getting the pointer to a specific component within
// an entity, given a variable name (the entity pointer) and a component type
#define ECS_GET_COMPONENT(_ecs, _name, _component, _key) \
    ((ECS##_component*) dynarray_get(                    \
        _ecs->_component,                                \
        _name->components[_key]));

// macro for generating ecs component switch statements and code to add them to
// an entity
#define ECS_RECIPE_MATCH(_ent_name, _cpt_name, _cpt_key)            \
    case _cpt_key: {                                                \
        ECS##_cpt_name *_cpt_name = malloc(sizeof(ECS##_cpt_name)); \
        ecs_##_cpt_name##_init(_cpt_name);                          \
        _ent_name->_cpt_name = _cpt_name;                           \
        break;                                                      \
    }

// generates a function to tick a specified component
#define ECS_TICK_COMPONENT(_name)                           \
    if (entity->_name != NULL) ecs_##_name##_tick(entity, entity->_name)

#define ECS_MOUSE_TICK_COMPONENT(_name)                             \
    if (entity->_name != NULL)                                      \
        ecs_##_name##_mouse_tick(entity, entity->_name, mouse_state)

#define ECS_FRAME_TICK_COMPONENT(_name)                 \
    if (entity->_name != NULL)                          \
        ecs_##_name##_frame_tick(entity, entity->_name)

typedef struct {
    // a list of all of the currently allocated entities
    DynArray *entities;
} ECSManager;

/*
 * Note that not all components will be ticked in update or in mouse update, as
 * some components don't require that functionality. Therefore, it would be a
 * waste of time to update them as components if their state is not going to
 * change.
 */

// allocates a new ECS on the stack
ECSManager *ecs_new(void);

// creates an entity from a recipe
Entity *ecs_create_entity(ECSManager*, ECSType*, size_t);

// deletes an entity and all associated memory
void ecs_delete_entity(ECSManager*, Entity*);

// updates all of the components in the ECS
void ecs_update(ECSManager*);

// calls mouse event on all components that support it within the ECS
void ecs_mouse_update(ECSManager*, MouseState*);

// updates entities every frame
void ecs_update_frame(ECSManager*);

// frees all data bound to the ECS including all memory allocated to entity
// components within the entity component list
void ecs_free(ECSManager*);

#endif
