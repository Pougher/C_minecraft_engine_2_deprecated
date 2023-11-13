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
                    x * CHUNK_X,
                    y * CHUNK_Y,
                    z * CHUNK_Z);

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
    for (i32 i = 0; i < WORLD_X * WORLD_Y * WORLD_Z; i++) {
        chunk_generate(world->chunks[i]);
        chunk_compute_mesh(world->chunks[i]);
    }
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
        || (world->centre[2] != world->player_pos->chunk_z)) {

        const int offset_x = world->centre[0] - world->player_pos->chunk_x;
        //const int offset_z = world->centre[2] - world->player_pos->chunk_z;

        if (offset_x == 1) {
            for (int i = WORLD_AREA - WORLD_X; i < WORLD_AREA; i++) {
                chunk_free(world->chunks[i]);
                world->chunks[i] = NULL;
            }
            memmove((char*)world->chunks + (WORLD_X * sizeof(Chunk*)),
                (char*)world->chunks,
                (WORLD_AREA - WORLD_X) * sizeof(Chunk*));
            for (int i = 0; i < WORLD_X; i++) {
                world->chunks[i] = chunk_new(
                    world->centre[0] * CHUNK_X,
                    0,
                    (world->centre[2] - 1 + i) * CHUNK_Z);
                chunk_generate(world->chunks[i]);
                chunk_compute_mesh(world->chunks[i]);
            }
        }

        if (offset_x == -1) {
            for (int i = 0; i < WORLD_X; i++) {
                chunk_free(world->chunks[i]);
                world->chunks[i] = NULL;
            }
            memmove((char*)world->chunks,
                (char*)world->chunks + WORLD_X * sizeof(Chunk*),
                (WORLD_AREA - WORLD_X) * sizeof(Chunk*));
            for (int i = 0; i < WORLD_X; i++) {
                world->chunks[i + (WORLD_AREA - WORLD_X)] = chunk_new(
                    (world->centre[0] - 1) * CHUNK_X,
                    0,
                    (world->centre[2] - 1 + i) * CHUNK_Z);
                chunk_generate(world->chunks[i + (WORLD_AREA - WORLD_X)]);
                chunk_compute_mesh(world->chunks[i + (WORLD_AREA - WORLD_X)]);
            }
        }

        /*
        for (i16 x = 0; x < WORLD_X; x++) {
            for (i16 y = 0; y < WORLD_Y; y++) {
                for (i16 z = 0; z < WORLD_Z; z++) {
                    i32 index = x + y * WORLD_X + z * (WORLD_X * WORLD_Y);

                    chunk_free(world->chunks[index]);

                    world->chunks[index] = chunk_new(
                        (world->centre[0] - (WORLD_X / 2) + x) * CHUNK_X,
                        y * CHUNK_Y,
                        (world->centre[2] - (WORLD_Z / 2) + z) * CHUNK_Z);

                    world->chunks[index]->rx = x;
                    world->chunks[index]->ry = y;
                    world->chunks[index]->rz = z;
                }
            }
        }
        world_generate(world);*/

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
