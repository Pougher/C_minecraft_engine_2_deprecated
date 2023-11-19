#include "gamestate.h"

struct GameState *state = NULL;

void gamestate_init(char *block_atlas_dir,
    char **shaders,
    i32 num_shaders) {
    state = malloc(sizeof(struct GameState));

    // load information about each block
    log_info("Calling init() on block information array...");
    block_init();

    // load the block texture atlas
    log_info("Calling init() on block atlas...");
    state->block_atlas = grid_atlas_new(block_atlas_dir,
        16,
        16,
        16,
        16);

    // initialize the world
    log_info("Calling init() on world...");
    state->world = world_new();

    // generate the world
    log_info("Generating world...");
    world_generate(state->world);

    // load all of the shaders
    log_info("Calling init() on shader array...");
    state->num_shaders = num_shaders;
    state->shaders = malloc(sizeof(Shader) * num_shaders);

    for (i32 i = 0; i < num_shaders; i++) {
        shader_load(&state->shaders[i], shaders[i * 2], shaders[i * 2 + 1]);
    }

    // the entity component system
    log_info("Calling init() on Entity Component System (ECS)");
    state->ecs = ecs_new();

    // create the player entity
    log_info("Creating the player entity");
    state->player = ecs_create_entity(state->ecs,
        (ECSType[]) {
            CAMERA,
            POSITION
        }, 2);

    ECSposition *pos = dynarray_get(
        state->ecs->position, ecs_get_component_id(state->player, POSITION));
    ECScamera *cam = dynarray_get(
        state->ecs->camera, ecs_get_component_id(state->player, CAMERA));

    camera_init(&cam->cam, &pos->pos);
    glm_vec3_copy((vec3) { WORLD_X * CHUNK_X / 2, 70, WORLD_Z * CHUNK_Z / 2 }, pos->pos);
    state->world->player_pos = pos;
}

void gamestate_free(void) {
    // free the world data
    world_free(state->world);

    // free the texture atlas
    grid_atlas_free(state->block_atlas);

    // free all shaders
    for (i32 i = 0; i < state->num_shaders; i++) {
        shader_delete(&state->shaders[i]);
    }
    free(state->shaders);

    // destroy the entity component system
    ecs_free(state->ecs);
}
