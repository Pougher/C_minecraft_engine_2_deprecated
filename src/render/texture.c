#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture *texture_new(char *filename, GLuint format) {
    stbi_set_flip_vertically_on_load(1);
    Texture *new_texture = malloc(sizeof(Texture));

    unsigned char *data = stbi_load(
        filename,
        &new_texture->width,
        &new_texture->height,
        &new_texture->channels,
        0);

    if (data == NULL) {
        char error_msg[32 + strlen(filename)];
        sprintf(error_msg, "Error loading texture '%s'", filename);
        log_error(error_msg);

        new_texture->id = 0;
        return new_texture;
    }

    // generate the OpenGL texture
    glGenTextures(1, &new_texture->id);
    glBindTexture(GL_TEXTURE_2D, new_texture->id);

    // set the texture attributes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // now that the texture is bound, we can start to generate it from the
    // previously loaded image data
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        new_texture->width,
        new_texture->height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data);

    // free the stb image data
    free(data);

#ifndef NO_LOGS
    char buffer[512 + strlen(filename)];
    sprintf(
        buffer,
        "Generated texture ID %d for '%s' with dimensions %dx%d",
        new_texture->id,
        filename,
        new_texture->width,
        new_texture->height);
    log_info(buffer);
#endif

    return new_texture;
}

Texture *texture_empty(int width, int height, GLuint format) {
    Texture *new_texture = malloc(sizeof(Texture));

    switch (format) {
        case GL_RGB: { new_texture->channels = 3; break; }
        case GL_RGBA: { new_texture->channels = 4; break; }
        default: {
            log_error(
                "Unsupported format passed to texture_empty");
            break;
        }
    }

    new_texture->width = width;
    new_texture->height = height;

    // generate an empty data array
    unsigned char *empty = calloc(new_texture->channels, width * height);

    glGenTextures(1, &new_texture->id);
    glBindTexture(GL_TEXTURE_2D, new_texture->id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        empty);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    free(empty);

    return new_texture;
}

double texture_normal_pixel_u(Texture *texture) {
    return (1.0f / (double)texture->width);
}

double texture_normal_pixel_v(Texture *texture) {
    return (1.0f / (double)texture->height);
}

void texture_free(Texture *texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}
