#include "ecs.h"

ECSManager *ecs_new(void) {
    ECSManager *manager = malloc(sizeof(ECSManager));
    manager->id = 0;

    ECS_COMPONENT(blockbreak);
    ECS_COMPONENT(position);
    ECS_COMPONENT(camera);
    ECS_COMPONENT(blockplace);

    return manager;
}

Entity *ecs_create_entity(ECSManager *manager,
    ECSType *recipe,
    size_t recipe_len) {
    Entity *entity = malloc(sizeof(Entity));

    entity->id = manager->id++;

    // zero all of the values held by the entity component tag list
    for (u32 i = 0; i < TOTAL_COMPONENTS; i++)
        entity->components[i] = ECS_EMPTY;

    size_t component_index;

    for (size_t i = 0; i < recipe_len; i++) {
        switch(recipe[i]) {
            ECS_RECIPE_MATCH(entity, position, POSITION);
            ECS_RECIPE_MATCH(entity, camera, CAMERA);
            ECS_RECIPE_MATCH(entity, blockbreak, BLOCKBREAK);
            ECS_RECIPE_MATCH(entity, blockplace, BLOCKPLACE);
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
    for (size_t i = 0; i < TOTAL_COMPONENTS; i++) {
        if (entity->components[i] != ECS_EMPTY) {
            switch (i) {
                ECS_DELETE(BLOCKBREAK, blockbreak);
                ECS_DELETE(POSITION, position);
                ECS_DELETE(CAMERA, camera);
            }
        }
    }
    free(entity);
}

void ecs_mouse_update(ECSManager *manager, MouseState *mouse_state) {
    ECS_MOUSE_TICK_COMPONENT(blockbreak);
    ECS_MOUSE_TICK_COMPONENT(blockplace);
}

void ecs_update(ECSManager *manager) {
    ECS_TICK_COMPONENT(position);
    ECS_TICK_COMPONENT(blockplace);
}

u64 ecs_get_component_id(Entity *entity, u64 id) {
    return entity->components[id];
}

void ecs_free(ECSManager *manager) {
    ECS_COMPONENT_FREE(position);
    ECS_COMPONENT_FREE(camera);
    ECS_COMPONENT_FREE(blockbreak);
    free(manager);
}
