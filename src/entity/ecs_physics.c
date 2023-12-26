#include "ecs_physics.h"
#include "entity.h"

#include "../common/gamestate.h"

void ecs_physics_init(ECSphysics *physics) {
    physics->grounded = false;

    glm_vec3_zero(physics->velocity);
    glm_vec3_zero(physics->av);
}

void ecs_physics_construct(ECSphysics *physics) {
    // calculate terminal velocity
    physics->terminal_velocity = -sqrt((2 * physics->mass * PHYSICS_GRAVITY) /
        (physics->fluid_density * physics->projected_area *
        physics->drag_coefficient));
    printf("%f\n", physics->terminal_velocity);
}

void ecs_physics_tick(struct Entity *entity, ECSphysics *physics) {
    (void) entity;

    glm_vec3_zero(physics->av);
}

void ecs_physics_frame_tick(struct Entity *entity, ECSphysics *physics) {
    vec3 temp;
    glm_vec3_add(physics->av, physics->velocity, temp);
    glm_vec3_scale(temp, state->delta, temp);
    glm_vec3_add(entity->position->pos, temp, entity->position->pos);
    printf("%f\n", physics->velocity[1]);
    if (world_get_block(state->world,
        (entity->position->pos)[0],
        (entity->position->pos)[1] - 2.0f,
        (entity->position->pos[2])) == AIR) {
        physics->velocity[1] -= PHYSICS_GRAVITY * state->delta;
        if (physics->velocity[1] < physics->terminal_velocity)
            physics->velocity[1] = physics->terminal_velocity;
        physics->grounded = false;
    } else {
        physics->velocity[1] = 0;
        entity->position->pos[1] = ceilf(entity->position->pos[1]);
        physics->grounded = true;
    }
    if (world_get_block(state->world,
        (entity->position->pos)[0],
        (entity->position->pos)[1],
        (entity->position->pos)[2]) != AIR
        && physics->velocity[1] > 0) {
        physics->velocity[1] = -0.1;
    }
}
