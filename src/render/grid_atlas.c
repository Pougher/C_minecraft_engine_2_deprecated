#include "grid_atlas.h"
#include "stb_image.h"

GridAtlas *grid_atlas_new(char *filename,
    int tile_w,
    int tile_h,
    int tiles_x,
    int tiles_y) {
    GridAtlas *new_atlas = malloc(sizeof(GridAtlas));

    new_atlas->tile_width = tile_w;
    new_atlas->tile_height = tile_h;
    new_atlas->tiles_x = tiles_x;
    new_atlas->tiles_y = tiles_y;

    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(
        filename,
        &new_atlas->width,
        &new_atlas->height,
        &new_atlas->channels,
        0);

    if (data == NULL) {
        char error_msg[32 + strlen(filename)];
        sprintf(error_msg, "Error loading grid atlas '%s'", filename);
        log_error(error_msg);

        return new_atlas;
    }

    unsigned char *atlas = calloc(sizeof(unsigned char),
        new_atlas->width * new_atlas->height * new_atlas->channels);

    const int image_row = (new_atlas->width * new_atlas->channels);
    const int tile_size_x = (tile_w * new_atlas->channels);
    const int tile_size = tile_w * tile_h * new_atlas->channels;

    for (int y = 0; y < tiles_y; y++) {
        for (int x = 0; x < tiles_x; x++) {
            unsigned char *ptr =
                data + (image_row * y * tiles_y) + tile_size_x * x;
            unsigned char *aptr = atlas + (y * tiles_y + x) * tile_size;

            for (int row = 0; row < tile_w; row++) {
                memcpy(
                    aptr + tile_size_x * row,
                    ptr + (image_row * row),
                    tile_size_x);
            }
        }
    }

    // Create the array texture from atlas
    new_atlas->atlas = array_texture_from_data(atlas,
        GL_RGBA,
        tile_w,
        tile_h,
        tiles_x * tiles_y);

    free(data);
    free(atlas);

    return new_atlas;
}

void grid_atlas_free(GridAtlas *atlas) {
    array_texture_free(atlas->atlas);
    free(atlas);
}
