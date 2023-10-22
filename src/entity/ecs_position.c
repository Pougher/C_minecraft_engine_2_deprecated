#include "ecs_position.h"

void ecs_position_init(ECSposition *component) {
    component->x = 0;
    component->y = 0;
    component->z = 0;
}
