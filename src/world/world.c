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
            }
        }
    }

    world->centre[0] = 0;
    world->centre[1] = 0;
    world->centre[2] = 0;

    // prevent a crash due to improper world sizing
    assert((WORLD_X % 2 != 0) && (WORLD_Z % 2 != 0) &&
        "World size cannot be a multiple of 2");

    return world;
}

void world_generate(World *world) {
    for (i32 i = 0; i < WORLD_X * WORLD_Y * WORLD_Z; i++) {
        chunk_generate(world->chunks[i]);
        chunk_compute_mesh(world->chunks[i]);
    }
}

// gets the chunk index from a given chunk location
static inline size_t world_chunk_offset(World *world, i64 x, i64 z) {
    return (x - (world->centre[0] - WORLD_X / 2)) +
        WORLD_X * (z - (world->centre[2] - WORLD_X / 2));
}

BlockType world_get_block(World *world, f64 x, f64 y, f64 z) {
    if (y >= CHUNK_Y) return AIR;

    i64 cx = (i64)x / CHUNK_X;
    i64 cz = (i64)z / CHUNK_Z;
    if (x < 0) {
        cx--;
    }
    if (z < 0) {
        cz--;
    }

    i32 chunk_coord_x = (x < 0 ? CHUNK_X - 1 : 0) + ((i64)x % CHUNK_X);
    i32 chunk_coord_z = (z < 0 ? CHUNK_Z - 1 : 0) + ((i64)z % CHUNK_Z);

    return chunk_get_block_offset(
        world->chunks[world_chunk_offset(world, cx, cz)],
        chunk_coord_x,
        y,
        chunk_coord_z);
}

float world_get_next_ground(World *world, f64 x, f64 y, f64 z) {
    for (float dy = floorf(y); dy > 0; dy--) {
        if (world_get_block(world, x, dy, z) != AIR) return dy;
    }
    return y + 1;
}

void world_set_block(World *world, f64 x, f64 y, f64 z, BlockType block) {
    if (y >= CHUNK_Y) return;

    i64 cx = (i64)x / CHUNK_X;
    i64 cz = (i64)z / CHUNK_Z;
    if (x < 0) {
        cx--;
    }
    if (z < 0) {
        cz--;
    }

    i32 chunk_coord_x = (x < 0 ? CHUNK_X - 1 : 0) + ((i64)x % CHUNK_X);
    i32 chunk_coord_z = (z < 0 ? CHUNK_Z - 1 : 0) + ((i64)z % CHUNK_Z);

    // I have no idea if this is a good solution, but it does work. However,
    // it was quite annoying to implement :/
    world->chunks[world_chunk_offset(world, cx, cz)]->blocks[
        chunk_compute_index(chunk_coord_x, y, chunk_coord_z)] = block;
    chunk_compute_mesh(world->chunks[world_chunk_offset(world, cx, cz)]);

    if (chunk_coord_x == 0) {
        int offset = world_chunk_offset(world, cx - 1, cz);
        world->chunks[offset]->blocks[
            chunk_compute_index(CHUNK_X, y, chunk_coord_z)] = block;
        chunk_compute_mesh(world->chunks[offset]);
    }

    if (chunk_coord_z == 0) {
        int offset = world_chunk_offset(world, cx, cz - 1);
        world->chunks[offset]->blocks[
            chunk_compute_index(chunk_coord_x, y, CHUNK_Z)] = block;
        chunk_compute_mesh(world->chunks[offset]);
    }

    if (chunk_coord_x == 1) {
        int offset = world_chunk_offset(world, cx - 1, cz);
        world->chunks[offset]->blocks[
            chunk_compute_index(
                CHUNK_X + CHUNK_OVERSCAN, y, chunk_coord_z)] = block;
        chunk_compute_mesh(world->chunks[offset]);
    }

    if (chunk_coord_z == 1) {
        int offset = world_chunk_offset(world, cx, cz - 1);
        world->chunks[offset]->blocks[
            chunk_compute_index(
                chunk_coord_x, y, CHUNK_Z + CHUNK_OVERSCAN)] = block;
        chunk_compute_mesh(world->chunks[offset]);
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

    for (i32 i = 0; i < WORLD_AREA; i++) {
        mesh_render(world->chunks[i]->transparent_mesh);
    }
}

// inline function to detect if a chunk is in bounds of the world at the current
// centre position
static inline bool world_chunk_in_bounds(World *world, i64 x, i64 y) {
    return llabs(x - world->centre[0]) <= (WORLD_X / 2) &&
        llabs(y - world->centre[2]) <= (WORLD_X / 2);
}

void world_update(World *world) {
    if ((world->centre[0] != world->player_pos->chunk_x)
        || (world->centre[2] != world->player_pos->chunk_z)) {
        // temporary storage of player x and y variables so I dont have to type
        // them out every single time
        const float px = world->player_pos->chunk_x;
        const float pz = world->player_pos->chunk_z;

        world->centre[0] = px;
        world->centre[2] = pz;

        // create a chunk backup
        Chunk *old[WORLD_AREA];
        memcpy(old, world->chunks, WORLD_AREA * sizeof(Chunk*));

        // Set world to unloaded chunks
        memset(world->chunks, 0, WORLD_AREA * sizeof(Chunk*));

        // place only in bounds chunks in to the new array
        for (size_t i = 0; i < WORLD_AREA; i++) {
            Chunk *chunk = old[i];
            if (chunk == NULL) {
                continue;
            } else if (world_chunk_in_bounds(world, chunk->cx, chunk->cz)) {
                world->chunks[world_chunk_offset(world, chunk->cx, chunk->cz)] =
                    chunk;
                continue;
            }
            chunk_free(chunk);
        }

        // generate all of the missing chunks
        for (size_t i = 0; i < WORLD_AREA; i++) {
            if (world->chunks[i] == 0) {
                int x = world->centre[0] + (i % WORLD_X) - (WORLD_X / 2);
                int z = world->centre[2] + (i / WORLD_X) - (WORLD_Z / 2);
                world->chunks[i] = chunk_new(x * CHUNK_X, 0, z * CHUNK_Z);
                chunk_generate(world->chunks[i]);
                chunk_compute_mesh(world->chunks[i]);
            }
        }
    }
}

void world_free(World *world) {
    for (i32 i = 0; i < WORLD_AREA; i++) {
        chunk_free(world->chunks[i]);
    }
    free(world->chunks);
    free(world);
}
