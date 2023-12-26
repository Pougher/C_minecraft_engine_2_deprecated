#include "ecs_position.h"

void ecs_position_init(ECSposition *component) {
    glm_vec3_copy(component->pos, (vec3) { 0, 0, 0 });
    component->chunk_x = 0;
    component->chunk_y = 0;
    component->chunk_z = 0;
}

void ecs_position_tick(struct Entity *entity, ECSposition *component) {
    (void) entity;
    component->chunk_x = (i64)(component->pos[0] / CHUNK_X);
    component->chunk_y = (i64)(component->pos[1] / CHUNK_Y);
    component->chunk_z = (i64)(component->pos[2] / CHUNK_Z);

    if (component->pos[0] < 0) component->chunk_x -= 1;
    if (component->pos[2] < 0) component->chunk_z -= 1;
}
