#include "entity_constructors.h"
#include "../common/gamestate.h"

Entity *player_construct(void) {
    // dimensions: 100cm * 40cm * 20cm
    Entity *player = ecs_create_entity(state->ecs,
        (ECSType[]) {
            CAMERA,
            POSITION,
            BLOCKBREAK,
            BLOCKPLACE,
            PLAYERCONTROLLER,
            PHYSICS
        }, 6);

    // setup physics values
    player->physics->drag_coefficient = 1.5f;
    player->physics->projected_area = 0.2 / BLOCK_SCALAR;
    player->physics->fluid_density = 1.293f;
    player->physics->mass = 9.0f; // 9kg

    ecs_physics_construct(player->physics);

    // initialize the player's camera
    camera_init(&player->camera->cam, &player->position->pos);

    // center the player
    glm_vec3_copy((vec3)
        { WORLD_X * CHUNK_X / 2, 60, WORLD_Z * CHUNK_Z / 2 },
        player->position->pos);

    // make sure that the world knows where the player is
    state->world->player_pos = player->position;

    return player;
}
