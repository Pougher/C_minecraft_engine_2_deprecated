#include "world.h"

World *world_new(void) {
    World *world = malloc(sizeof(World));
    world->chunks = malloc(sizeof(Chunk*) * WORLD_AREA);

    world->width = WORLD_X;
    world->height = WORLD_Y;
    world->depth = WORLD_Z;

    for (int x = 0; x < WORLD_X; x++) {
        for (int y = 0; y < WORLD_Y; y++) {
            for (int z = 0; z < WORLD_Z; z++) {
                int index = x + y * WORLD_X + z * (WORLD_X * WORLD_Y);

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


    return world;
}

void world_generate(World *world) {
    int total_vertices = 0;

    for (int i = 0; i < WORLD_X * WORLD_Y * WORLD_Z; i++) {
        chunk_generate(world->chunks[i]);
        chunk_compute_mesh(world->chunks[i]);
        total_vertices += world->chunks[i]->solid_mesh->vertices_length;
        total_vertices += world->chunks[i]->fluid_mesh->vertices_length;
    }

    char buf[64];
    sprintf(buf, "World vertices count: %d", total_vertices);
    log_info(buf);
}

void world_render(World *world) {
    for (int i = 0; i < WORLD_AREA; i++) {
        mesh_render(world->chunks[i]->solid_mesh);
    }

    // after the first solid geometry pass, render the translucent geometry
    for (int i = 0; i < WORLD_AREA; i++) {
        mesh_render(world->chunks[i]->fluid_mesh);
    }
}

void world_free(World *world) {
    for (int i = 0; i < WORLD_AREA; i++) {
        chunk_free(world->chunks[i]);
    }
    free(world);
}
