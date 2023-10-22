#include "ecs.h"

ECSManager *ecs_new(void) {
    ECSManager *manager = malloc(sizeof(ECSManager));
    manager->id = 0;

    ECS_COMPONENT(position);
    ECS_COMPONENT(camera);

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

    for (size_t i = 0; i < recipe_len; i++) {
        switch(recipe[i]) {
            case POSITION: {
                ECS_ADD_COMPONENT(position);
                entity->components[POSITION] = manager->position->length - 1;
                break;
            }
            case CAMERA: {
                ECS_ADD_COMPONENT(camera);
                entity->components[CAMERA] = manager->camera->length - 1;
                break;
            }
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
                ECS_DELETE(POSITION, position);
            }
        }
    }
    free(entity);
}

void ecs_update(ECSManager *manager) {
    (void) manager;
}

u64 ecs_get_component_id(Entity *entity, u64 id) {
    return entity->components[id];
}

void ecs_free(ECSManager *manager) {
    ECS_COMPONENT_FREE(position);
    free(manager);
}
