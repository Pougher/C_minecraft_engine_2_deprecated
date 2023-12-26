#include "ecs.h"

ECSManager *ecs_new(void) {
    ECSManager *manager = malloc(sizeof(ECSManager));
    manager->entities = dynarray_new(sizeof(Entity*));

    return manager;
}

Entity *ecs_create_entity(ECSManager *manager,
    ECSType *recipe,
    size_t recipe_len) {
    Entity *entity = calloc(1, sizeof(Entity));

    size_t idx;

    // add the new entity pointer to the array of entity pointers
    dynarray_push_index(manager->entities, &entity, &idx);

    entity->id = idx + 1;

    for (size_t i = 0; i < recipe_len; i++) {
        switch(recipe[i]) {
            ECS_RECIPE_MATCH(entity, position, POSITION);
            ECS_RECIPE_MATCH(entity, camera, CAMERA);
            ECS_RECIPE_MATCH(entity, blockbreak, BLOCKBREAK);
            ECS_RECIPE_MATCH(entity, blockplace, BLOCKPLACE);
            ECS_RECIPE_MATCH(entity, physics, PHYSICS);
            ECS_RECIPE_MATCH(entity, playercontroller, PLAYERCONTROLLER);
            default: {
                char buf[128];
                sprintf(buf, "Cannot construct ecs component %d as it is not "
                        "defined.", (int)recipe[i]);
                log_warning(buf);
                break;
            }
        }
    }

    return entity;
}

void ecs_delete_entity(ECSManager *ecs, Entity *entity) {
    ECS_DELETE(blockbreak);
    ECS_DELETE(blockplace);
    ECS_DELETE(physics);
    ECS_DELETE(position);
    ECS_DELETE(camera);
    ECS_DELETE(playercontroller);
    dynarray_reserve_delete(ecs->entities, entity->id);
}

void ecs_mouse_update(ECSManager *manager, MouseState *mouse_state) {
    for (size_t i = 0; i < manager->entities->length; i++) {
        Entity *entity = *((Entity**)dynarray_get(manager->entities, i));

        ECS_MOUSE_TICK_COMPONENT(blockbreak);
        ECS_MOUSE_TICK_COMPONENT(blockplace);
    }
}

void ecs_update(ECSManager *manager) {
    // again it is very important that physics is ticked before anything else
    // to ensure velocities are additive
    for (size_t i = 0; i < manager->entities->length; i++) {
        Entity *entity = *((Entity**)dynarray_get(manager->entities, i));

        ECS_TICK_COMPONENT(physics);
        ECS_TICK_COMPONENT(playercontroller);
        ECS_TICK_COMPONENT(position);
        ECS_TICK_COMPONENT(blockplace);
    }
}

void ecs_update_frame(ECSManager *manager) {
    // must be ticked first, as if it isn't, all additional changes to the
    // velocity of the controller will be negated
    for (size_t i = 0; i < manager->entities->length; i++) {
        Entity *entity = *((Entity**)dynarray_get(manager->entities, i));

        ECS_FRAME_TICK_COMPONENT(physics);
    }
}

void ecs_free(ECSManager *manager) {
    for (size_t i = 0; i < manager->entities->length; i++) {
        Entity *entity = *((Entity**)dynarray_get(manager->entities, i));

        ECS_COMPONENT_FREE(position);
        ECS_COMPONENT_FREE(camera);
        ECS_COMPONENT_FREE(blockplace);
        ECS_COMPONENT_FREE(blockbreak);
        ECS_COMPONENT_FREE(physics);
        ECS_COMPONENT_FREE(playercontroller);
    }

    dynarray_free(manager->entities);
    free(manager);
}
