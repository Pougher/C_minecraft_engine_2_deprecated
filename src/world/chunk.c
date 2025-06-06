#include "chunk.h"
#include "../common/gamestate.h"

Chunk *chunk_new(i64 x, i64 y, i64 z) {
    Chunk *chunk = malloc(sizeof(Chunk));
    chunk->blocks = malloc(sizeof(BlockType)
        * CHUNK_OVERSCAN_X
        * CHUNK_OVERSCAN_Y
        * CHUNK_OVERSCAN_Z);

    // setup the mesh with (x, y, z) and texture (u, v) coordinates
    chunk->solid_mesh = mesh_new();
    chunk->fluid_mesh = mesh_new();
    chunk->transparent_mesh = mesh_new();

    // vertex position attribute, 1 extra int for block id and uvs
    mesh_add_attribute(chunk->solid_mesh, (MeshAttribute) {
        .index = (void*) 0,
        .size = 3,
        .type = GL_FLOAT,
        .bytes = sizeof(float) * 3 });

    mesh_add_attribute(chunk->solid_mesh, (MeshAttribute) {
        .index = (void*) (3 * sizeof(float)),
        .size = 3,
        .type = GL_FLOAT,
        .bytes = sizeof(float) * 3 });

    mesh_copy_attributes(chunk->fluid_mesh, chunk->solid_mesh);
    mesh_copy_attributes(chunk->transparent_mesh, chunk->solid_mesh);

    for (int i = 0; i <
        CHUNK_OVERSCAN_X * CHUNK_OVERSCAN_Y * CHUNK_OVERSCAN_Z; i++)
        chunk->blocks[i] = AIR;

    chunk->x = x;
    chunk->y = y;
    chunk->z = z;

    chunk->cx = x / CHUNK_X;
    chunk->cy = y / CHUNK_Y;
    chunk->cz = z / CHUNK_Z;

    return chunk;
}

// tests the sides of a block and returns a bitset
static u8 chunk_test_adjacent_solid(Chunk *chunk, i32 x, i32 y, i32 z) {
    u8 result = 0;

    result |=
        !(state->blocks[chunk_get_block(chunk, x - 1, y, z)].transparent
        || state->blocks[chunk_get_block(chunk, x - 1, y, z)].fluid);
    result |=
        !(state->blocks[chunk_get_block(chunk, x + 1, y, z)].transparent
        || state->blocks[chunk_get_block(chunk, x + 1, y, z)].fluid) << 1;
    result |=
        !(state->blocks[chunk_get_block(chunk, x, y - 1, z)].transparent
        || state->blocks[chunk_get_block(chunk, x, y - 1, z)].fluid) << 2;
    result |=
        !(state->blocks[chunk_get_block(chunk, x, y + 1, z)].transparent
        || state->blocks[chunk_get_block(chunk, x, y + 1, z)].fluid) << 3;
    result |=
        !(state->blocks[chunk_get_block(chunk, x, y, z - 1)].transparent
        || state->blocks[chunk_get_block(chunk, x, y, z - 1)].fluid) << 4;
    result |=
        !(state->blocks[chunk_get_block(chunk, x, y, z + 1)].transparent
        || state->blocks[chunk_get_block(chunk, x, y, z + 1)].fluid) << 5;
    return ~result;
}

// test the sides of chunks for translucent geometry
static i8 chunk_test_adjacent_fluid(Chunk *chunk, i32 x, i32 y, i32 z) {
    i8 result = 0;

    result |= (state->blocks[chunk_get_block(chunk, x - 1, y, z)].transparent);
    result |= (state->blocks[chunk_get_block(chunk, x + 1, y, z)].transparent)
        << 1;
    result |= (state->blocks[chunk_get_block(chunk, x, y - 1, z)].transparent)
        << 2;
    result |= (state->blocks[chunk_get_block(chunk, x, y + 1, z)].transparent)
        << 3;
    result |= (state->blocks[chunk_get_block(chunk, x, y, z - 1)].transparent)
        << 4;
    result |= (state->blocks[chunk_get_block(chunk, x, y, z + 1)].transparent)
        << 5;

    // invert the bits of the result such that a 1 denotes that the face has not
    // got any block adjacent to it on that side
    return result;
}

// generate multiple octaves of simplex noise
static inline double chunk_octave_noise(struct osn_context *ctx,
    i32 octaves,
    f64 x,
    f64 y,
    f64 frequency,
    f64 amplitude,
    f64 persistence,
    f64 lacunarity) {
    f64 value = 0;

    for (i32 i = 0; i < octaves; i++) {
        value +=
            amplitude * open_simplex_noise2(ctx, x * frequency, y * frequency);
        amplitude *= persistence;
        frequency *= lacunarity;
    }

    return value;
}

// chunk tree generation algorithm
static void chunk_generate_tree(Chunk *chunk, i32 index, i32 x, i32 y, i32 z) {
    for (i32 i = x - 2; i < x + 3; i++) {
        for (i32 j = z - 2; j < z + 3; j++) {
            chunk_set_block(chunk, i, y + 3, j, LEAVES);
            chunk_set_block(chunk, i, y + 4, j, LEAVES);
        }
    }
    for (i32 i = x - 1; i < x + 2; i++) {
        for (i32 j = z - 1; j < z + 2; j++) {
            chunk_set_block(chunk, i, y + 5, j, LEAVES);
        }
    }

    for (i32 i = 0; i < 4; i++) {
        chunk->blocks[index + i * CHUNK_OVERSCAN_X] = WOOD;
    }

    // finish off the trees with the + shaped bit at the top (hardcoded because
    // I can't be bothered to do it with for loops)
    chunk_set_block(chunk, x + 1, y + 6, z, LEAVES);
    chunk_set_block(chunk, x, y + 6, z + 1, LEAVES);
    chunk_set_block(chunk, x - 1, y + 6, z, LEAVES);
    chunk_set_block(chunk, x, y + 6, z - 1, LEAVES);
}

void chunk_generate(Chunk *chunk) {
    // open simplex noise struct
    struct osn_context *ctx;
    open_simplex_noise(69420, &ctx);

    // seed the random number generator
    srand(69420);

    for (i32 x = 0; x < CHUNK_OVERSCAN_X; x++) {
        for (i32 z = 0; z < CHUNK_OVERSCAN_Z; z++) {
            f64 ax = x + chunk->x - CHUNK_OVERSCAN;
            f64 az = z + chunk->z - CHUNK_OVERSCAN;

            f64 v = chunk_octave_noise(ctx, 4, ax, az, 0.01, 1, 0.5, 2.0);
            int val = ((v + 1.0) / 2) * (CHUNK_Y / 3) + 30;

            for (i32 y = 0; y < CHUNK_OVERSCAN_Y; y++) {
                i32 i = chunk_compute_index(x, y, z);
                if (y < 47) chunk->blocks[i] = WATER;
                if (y == val) {
                    chunk->blocks[i] = GRASS;
                }
                // note: trees should not be generated in the chunk overscan
                // area. Thus, only generate trees between the edge of the chunk
                // plus 1 and its maximum size plus 1
                if (y == val + 1 && y >= 50 && x > 1 && x < CHUNK_X - 1 &&
                    z > 1 && z < CHUNK_X - 1) {
                    // random number to check if we should generate a tree
                    i32 chance = rand() % CHUNK_TREE_CHANCE;
                    if (chance == 1) {
                        chunk_generate_tree(chunk, i, x, y, z);
                    }
                }
                if (y < val) {
                    chunk->blocks[i] = DIRT;
                }
                if (y == val && val < 50) chunk->blocks[i] = SAND;
                if (y < (f64)val * 0.8) chunk->blocks[i] = STONE;
                if (y == CHUNK_OVERSCAN) chunk->blocks[i] = BEDROCK;
            }
        }
    }

    open_simplex_noise_free(ctx);
}

void chunk_compute_mesh(Chunk *chunk) {
    i32 ax, ay, az = 0;

    vec4 box = { 0.0f, 0.0f, 1.0f, 1.0f };

    // reset the chunks mesh information
    mesh_reset(chunk->fluid_mesh);
    mesh_reset(chunk->solid_mesh);
    mesh_reset(chunk->transparent_mesh);

    for (i32 x = CHUNK_OVERSCAN; x < CHUNK_OVERSCAN_X - CHUNK_OVERSCAN; x++) {
        for (i32 y = CHUNK_OVERSCAN; y < CHUNK_OVERSCAN_Y - CHUNK_OVERSCAN; y++) {
            for (i32 z = CHUNK_OVERSCAN; z < CHUNK_OVERSCAN_Z - CHUNK_OVERSCAN; z++) {
                i32 i = x + (y * CHUNK_OVERSCAN_X)
                    + (z * CHUNK_OVERSCAN_X * CHUNK_OVERSCAN_Y);
                // if the block is air, dont bother to do any other
                // computations
                if (chunk->blocks[i] == AIR) continue;

                // adjacency test for solids and liquids + mesh selection
                i8 adj;
                Mesh *mesh;

                if (state->blocks[chunk->blocks[i]].fluid) {
                    adj = chunk_test_adjacent_fluid(chunk, x, y, z);
                    mesh = chunk->fluid_mesh;
                } else if (state->blocks[chunk->blocks[i]].transparent) {
                    adj = 0xff;
                    mesh = chunk->transparent_mesh;
                } else {
                    adj = chunk_test_adjacent_solid(chunk, x, y, z);
                    mesh = chunk->solid_mesh;
                }

                ax = x + chunk->x;
                ay = y + chunk->y;
                az = z + chunk->z;

                i32 index;

                if (adj & 0x10) {
                    BLOCK_UV_POS(BACKWARD, index);
                    mesh_add_data(
                        mesh,
                        BLOCK_FACE_0(ax, ay, az, box, index),
                        sizeof(f32),
                        36,
                        6);
                }
                if (adj & 0x20) {
                    BLOCK_UV_POS(FORWARD, index);
                    mesh_add_data(
                        mesh,
                        BLOCK_FACE_1(ax, ay, az, box, index),
                        sizeof(f32),
                        36,
                        6);
                }
                if (adj & 0x01) {
                    BLOCK_UV_POS(LEFT, index);
                    mesh_add_data(
                        mesh,
                        BLOCK_FACE_2(ax, ay, az, box, index),
                        sizeof(f32),
                        36,
                        6);
                }
                if (adj & 0x02) {
                    BLOCK_UV_POS(RIGHT, index);
                    mesh_add_data(
                        mesh,
                        BLOCK_FACE_3(ax, ay, az, box, index),
                        sizeof(f32),
                        36,
                        6);
                }
                if (adj & 0x04) {
                    BLOCK_UV_POS(DOWN, index);
                    mesh_add_data(
                        mesh,
                        BLOCK_FACE_4(ax, ay, az, box, index),
                        sizeof(f32),
                        36,
                        6);
                }
                if (adj & 0x08) {
                    BLOCK_UV_POS(UP, index);
                    mesh_add_data(
                        mesh,
                        BLOCK_FACE_5(ax, ay, az, box, index),
                        sizeof(f32),
                        36,
                        6);
                }
            }
        }
    }

    mesh_compute_buffers(chunk->solid_mesh);
    mesh_compute_buffers(chunk->fluid_mesh);
    mesh_compute_buffers(chunk->transparent_mesh);
}

BlockType chunk_get_block(Chunk *chunk, i32 x, i32 y, i32 z) {
    if (x < 0 ||
        y < 0 ||
        z < 0 ||
        x >= CHUNK_OVERSCAN_X ||
        y >= CHUNK_OVERSCAN_Y ||
        z >= CHUNK_OVERSCAN_Z) {
        return AIR;
    }
    i32 index = x + (y * CHUNK_OVERSCAN_X)
        + (z * CHUNK_OVERSCAN_X * CHUNK_OVERSCAN_Y);
    return chunk->blocks[index];
}

BlockType chunk_get_block_offset(Chunk *chunk, i32 x, i32 y, i32 z) {
    if (x < 0 ||
        y < 0 ||
        z < 0 ||
        x >= CHUNK_OVERSCAN_X ||
        y >= CHUNK_OVERSCAN_Y ||
        z >= CHUNK_OVERSCAN_Z) {
        return AIR;
    }
    size_t index = chunk_compute_index(x, y, z);
    return chunk->blocks[index];
}

size_t chunk_compute_index(i32 x, i32 y, i32 z) {
    return x + y * CHUNK_OVERSCAN_X + z * CHUNK_OVERSCAN_X * CHUNK_OVERSCAN_Y;
}

void chunk_set_block(Chunk *chunk, i32 x, i32 y, i32 z, BlockType t) {
    if (x < 0 ||
        y < 0 ||
        z < 0 ||
        x >= CHUNK_OVERSCAN_X ||
        y >= CHUNK_OVERSCAN_Y ||
        z >= CHUNK_OVERSCAN_Z) {
        return;
    }
    chunk->blocks[chunk_compute_index(x, y, z)] = t;
}

void chunk_free(Chunk *chunk) {
    mesh_free(chunk->solid_mesh);
    mesh_free(chunk->fluid_mesh);
    mesh_free(chunk->transparent_mesh);
    free(chunk->blocks);
    free(chunk);
}
