#ifndef TEXTURE_ARRAY_H
#define TEXTURE_ARRAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "../common/log.h"

typedef struct {
    // the width of each texture
    int width;

    // the height of each texture
    int height;

    // the number of textures in the texture array
    int images;

    // the number of channels in each texture
    int channels;

    // the OpenGL ID of the texture
    unsigned int id;
} ArrayTexture;

// Creates a new OpenGL array texture object and sets each texture to be the
// width and height specified. The last parameter specifies the number of
// textures in the resultant texture array
ArrayTexture *array_texture_new(char*, GLuint, int, int, int);

// Generates an array texture from the data provided to the function
ArrayTexture *array_texture_from_data(unsigned char*, GLuint, int, int, int);

// Frees the allocated Texture, also deletes the texture within OpenGL
void array_texture_free(ArrayTexture*);

#endif
