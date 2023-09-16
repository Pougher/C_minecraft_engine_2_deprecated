#include "world.h"

World *world_new(void) {
    World *world = malloc(sizeof(World));
    world->chunks = malloc(sizeof(Chunk*) * WORLD_AREA);

    for (int x = 0; x < WORLD_X; x++) {
        for (int y = 0; y < WORLD_Y; y++) {
            for (int z = 0; z < WORLD_Z; z++) {
                int index = z + WORLD_Z * (y + WORLD_Y * x);

                world->chunks[index] = chunk_new(
                    x * CHUNK_X,
                    y * CHUNK_Y,
                    z * CHUNK_Z);

                chunk_compute_mesh(world->chunks[index]);
            }
        }
    }

    return world;
}

void world_render(World *world) {
    for (int i = 0; i < WORLD_AREA; i++) {
        mesh_render(world->chunks[i]->mesh);
    }
}

void world_free(World *world) {
    for (int i = 0; i < WORLD_AREA; i++) {
        chunk_free(world->chunks[i]);
    }
    free(world);
}
