#include "ecs.h"

ECSManager *ecs_new(void) {
    ECSManager *manager = malloc(sizeof(ECSManager));

    ECS_COMPONENT(position);

    return manager;
}

void ecs_free(ECSManager *manager) {
    ECS_COMPONENT_FREE(position);
    free(manager);
}
