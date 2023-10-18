#include "gamestate.h"

struct GameState *state = NULL;

void gamestate_init(char *block_atlas_dir,
    char **shaders,
    i32 num_shaders) {
    state = malloc(sizeof(struct GameState));

    // load information about each block
    log_info("Calling init() on block information array...");
    block_init();

    // first, allocate and initialize the player camera
    log_info("Calling init() on player camera...");
    state->player_camera = malloc(sizeof(Camera));
    camera_init(state->player_camera, (vec3) { 0.0f, 0.0f, 0.0f });

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
}

void gamestate_free(void) {
    // first, free the player camera
    free(state->player_camera);

    // then, free the world
    world_free(state->world);

    // free the texture atlas
    grid_atlas_free(state->block_atlas);

    // free all shaders
    for (i32 i = 0; i < state->num_shaders; i++) {
        shader_delete(&state->shaders[i]);
    }

    free(state->shaders);
}
