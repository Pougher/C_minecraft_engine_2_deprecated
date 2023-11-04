#include "world.h"
#include "../common/gamestate.h"

World *world_new(void) {
    World *world = malloc(sizeof(World));
    world->chunks = malloc(sizeof(Chunk*) * WORLD_AREA);

    world->width = WORLD_X;
    world->height = WORLD_Y;
    world->depth = WORLD_Z;

    for (i16 x = 0; x < WORLD_X; x++) {
        for (i16 y = 0; y < WORLD_Y; y++) {
            for (i16 z = 0; z < WORLD_Z; z++) {
                i32 index = x + y * WORLD_X + z * (WORLD_X * WORLD_Y);

                world->chunks[index] = chunk_new(
                    (x - WORLD_X / 2) * CHUNK_X,
                    (y - WORLD_Y / 2) * CHUNK_Y,
                    (z - WORLD_Z / 2) * CHUNK_Z);

                world->chunks[index]->rx = x;
                world->chunks[index]->ry = y;
                world->chunks[index]->rz = z;
            }
        }
    }

    world->centre[0] = 0;
    world->centre[1] = 0;
    world->centre[2] = 0;

    return world;
}

void world_generate(World *world) {
    i64 total_vertices = 0;

    for (i32 i = 0; i < WORLD_X * WORLD_Y * WORLD_Z; i++) {
        chunk_generate(world->chunks[i]);
        chunk_compute_mesh(world->chunks[i]);
        total_vertices += world->chunks[i]->solid_mesh->vertices_length;
        total_vertices += world->chunks[i]->fluid_mesh->vertices_length;
    }

    char buf[64];
    sprintf(buf, "World vertices count: %" PRId64, total_vertices);
    log_info(buf);
}

void world_render(World *world) {
    for (i32 i = 0; i < WORLD_AREA; i++) {
        mesh_render(world->chunks[i]->solid_mesh);
    }

    // after the first solid geometry pass, render the translucent geometry
    for (i32 i = 0; i < WORLD_AREA; i++) {
        mesh_render(world->chunks[i]->fluid_mesh);
    }
}

void world_update(World *world) {
    if ((world->centre[0] != world->player_pos->chunk_x)
        != (world->centre[1] != world->player_pos->chunk_y)
        != (world->centre[2] != world->player_pos->chunk_z)) {

        int rel_chunk_x = world->centre[0] - world->player_pos->chunk_x;
        int rel_chunk_z = world->centre[2] - world->player_pos->chunk_z;
        printf("%d %d\n", rel_chunk_x, rel_chunk_z);

        for (i16 x = 0; x < WORLD_X; x++) {
            for (i16 y = 0; y < WORLD_Y; y++) {
                for (i16 z = 0; z < WORLD_Z; z++) {
                    i32 index = x + y * WORLD_X + z * (WORLD_X * WORLD_Y);

                    world->chunks[index] = chunk_new(
                        (world->centre[0] + x) * CHUNK_X,
                        (world->centre[1] + y) * CHUNK_Y,
                        (world->centre[2] + z) * CHUNK_Z);

                    world->chunks[index]->rx = x;
                    world->chunks[index]->ry = y;
                    world->chunks[index]->rz = z;
                }
            }
        }
        world_generate(world);

        world->centre[0] = world->player_pos->chunk_x;
        world->centre[1] = world->player_pos->chunk_y;
        world->centre[2] = world->player_pos->chunk_z;
    }
}

void world_free(World *world) {
    for (i32 i = 0; i < WORLD_AREA; i++) {
        chunk_free(world->chunks[i]);
    }
    free(world);
}
