#include "chunk.h"
#include "../common/gamestate.h"

Chunk *chunk_new(int64_t x, int64_t y, int64_t z) {
    Chunk *chunk = malloc(sizeof(Chunk));
    chunk->blocks = malloc(sizeof(BlockType) * CHUNK_X * CHUNK_Y * CHUNK_Z);

    // setup the mesh with (x, y, z) and texture (u, v) coordinates
    chunk->mesh = mesh_new();

    // vertex position attribute, 1 extra int for block id and uvs
    mesh_add_attribute(chunk->mesh, (MeshAttribute) {
        .index = (void*) 0,
        .size = 3,
        .type = GL_FLOAT,
        .bytes = sizeof(float) * 3 });

    mesh_add_attribute(chunk->mesh, (MeshAttribute) {
        .index = (void*) (3 * sizeof(float)),
        .size = 3,
        .type = GL_FLOAT,
        .bytes = sizeof(float) * 3 });


    for (int i = 0; i < CHUNK_X * CHUNK_Y * CHUNK_Z; i++)
        chunk->blocks[i] = DIRT;

    chunk->x = x;
    chunk->y = y;
    chunk->z = z;

    return chunk;
}

// tests the sides of a block and returns a bitset
static uint8_t chunk_test_adjacent(Chunk *chunk, int x, int y, int z) {
    uint8_t result = 0;

    result |= (chunk_get_block(chunk, x - 1, y, z) != AIR);
    result |= (chunk_get_block(chunk, x + 1, y, z) != AIR) << 1;
    result |= (chunk_get_block(chunk, x, y - 1, z) != AIR) << 2;
    result |= (chunk_get_block(chunk, x, y + 1, z) != AIR) << 3;
    result |= (chunk_get_block(chunk, x, y, z - 1) != AIR) << 4;
    result |= (chunk_get_block(chunk, x, y, z + 1) != AIR) << 5;

    // invert the bits of the result such that a 1 denotes that the face has not
    // got any block adjacent to it on that side
    return ~result;
}

void chunk_compute_mesh(Chunk *chunk) {
    int x, y, z, ax, ay, az = 0;

    vec4 box = { 0.0f, 0.0f, 1.0f, 1.0f };

    for (int i = 0; i < CHUNK_X * CHUNK_Y * CHUNK_Z; i++) {
        z = i / (CHUNK_X * CHUNK_Y);
        int remainder = i % (CHUNK_X * CHUNK_Y);
        y = remainder / CHUNK_X;
        x = remainder % CHUNK_X;

        ax = x + chunk->x;
        ay = y + chunk->y;
        az = z + chunk->z;

        uint8_t adj = chunk_test_adjacent(chunk, x, y, z);

        int index;

        if (adj & 0x10) {
            BLOCK_UV_POS(BACKWARD, index);
            mesh_add_data(
                chunk->mesh,
                BLOCK_FACE_0(ax, ay, az, box, index),
                sizeof(float),
                36,
                6);
        }
        if (adj & 0x20) {
            BLOCK_UV_POS(FORWARD, index);
            mesh_add_data(
                chunk->mesh,
                BLOCK_FACE_1(ax, ay, az, box, index),
                sizeof(float),
                36,
                6);
        }
        if (adj & 0x01) {
            BLOCK_UV_POS(LEFT, index);
            mesh_add_data(
                chunk->mesh,
                BLOCK_FACE_2(ax, ay, az, box, index),
                sizeof(float),
                36,
                6);
        }
        if (adj & 0x02) {
            BLOCK_UV_POS(RIGHT, index);
            mesh_add_data(
                chunk->mesh,
                BLOCK_FACE_3(ax, ay, az, box, index),
                sizeof(float),
                36,
                6);
        }
        if (adj & 0x04) {
            BLOCK_UV_POS(DOWN, index);
            mesh_add_data(
                chunk->mesh,
                BLOCK_FACE_4(ax, ay, az, box, index),
                sizeof(float),
                36,
                6);
        }
        if (adj & 0x08) {
            BLOCK_UV_POS(UP, index);
            mesh_add_data(
                chunk->mesh,
                BLOCK_FACE_5(ax, ay, az, box, index),
                sizeof(float),
                36,
                6);
        }
    }

    mesh_compute_buffers(chunk->mesh);
}

BlockType chunk_get_block(Chunk *chunk, int x, int y, int z) {
    if (x < 0 ||
        y < 0 ||
        z < 0 ||
        x >= CHUNK_X ||
        y >= CHUNK_Y ||
        z >= CHUNK_Z) {
        return AIR;
    }
    int index = z + CHUNK_Z * (y + CHUNK_Y * x);
    return chunk->blocks[index];
}

void chunk_free(Chunk *chunk) {
    mesh_free(chunk->mesh);
    free(chunk->blocks);
    free(chunk);
}

