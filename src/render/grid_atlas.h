#ifndef GRID_ATLAS_H
#define GRID_ATLAS_H

#include <stdio.h>
#include <stdlib.h>

#include "../common/log.h"
#include "array_texture.h"

typedef struct {
    // the texture containing the atlas data
    ArrayTexture *atlas;

    // the width of the image
    int width;

    // the height of the image
    int height;

    // the number of channels in the image
    int channels;

    // the width of each individual texture in the atlas
    int tile_width;

    // the height of each individual texture in the atlas
    int tile_height;

    // the number of tiles in the x direction of the atlas
    int tiles_x;

    // the number of tiles in the y direction of the atlas
    int tiles_y;
} GridAtlas;

// Creates a new grid atlas from the filename and the number of tiles
GridAtlas *grid_atlas_new(char*, int, int, int, int);

// Frees all resources allocated to the grid atlas
void grid_atlas_free(GridAtlas*);

#endif
