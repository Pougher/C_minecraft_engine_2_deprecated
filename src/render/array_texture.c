#include "array_texture.h"
#include "stb_image.h"

// function that can be reused to produce array textures
static inline void create_texture(int width,
    int height,
    int count,
    GLuint format,
    unsigned char *data,
    unsigned int *id) {

    glGenTextures(1, id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, *id);

    // set the texture attributes
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // now that all of the parameters have been set up we can start to
    // generate the array texture
    glTexImage3D(GL_TEXTURE_2D_ARRAY,
        0,
        GL_RGBA,
        width,
        height,
        count,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data);
}

ArrayTexture *array_texture_new(char *filename,
    GLuint format,
    int width,
    int height,
    int count) {
    stbi_set_flip_vertically_on_load(1);
    ArrayTexture *new_texture = malloc(sizeof(ArrayTexture));

    unsigned char *data = stbi_load(
        filename,
        &new_texture->width,
        &new_texture->height,
        &new_texture->channels,
        0);

    if (data == NULL) {
        char error_msg[32 + strlen(filename)];
        sprintf(error_msg, "Error loading array texture '%s'", filename);
        log_error(error_msg);

        new_texture->id = 0;
        return new_texture;
    }

    // set the variable containing the number of images
    new_texture->images = count;

    // create the texture
    create_texture(width,
        height,
        count,
        format,
        data,
        &new_texture->id);

    // free the loaded image data
    free(data);

#ifndef NO_LOGS
    char buffer[512 + strlen(filename)];
    sprintf(
        buffer,
        "Generated array texture ID %d for '%s' with dimensions %dx%dx%d",
        new_texture->id,
        filename,
        new_texture->width,
        new_texture->height,
        new_texture->images);
    log_info(buffer);
#endif

    return new_texture;
}

// unlike texture_empty, the texture is not filled in
ArrayTexture *array_texture_from_data(unsigned char *data,
    GLuint format,
    int width,
    int height,
    int count) {
    ArrayTexture *new_texture = malloc(sizeof(ArrayTexture));

    switch (format) {
        case GL_RGB: { new_texture->channels = 3; break; }
        case GL_RGBA: { new_texture->channels = 4; break; }
        default: {
            log_error(
                "Unsupported format passed to array_texture_empty");
            break;
        }
    }

    // set the parameters of the array texture
    new_texture->width = width;
    new_texture->height = height;
    new_texture->images = count;

    // create the texture
    create_texture(width, height, count, format, data, &new_texture->id);

#ifndef NO_LOGS
    char buffer[512];
    sprintf(
        buffer,
        "Generated array texture ID %d with dimensions %dx%dx%d",
        new_texture->id,
        new_texture->width,
        new_texture->height,
        new_texture->images);
    log_info(buffer);
#endif

    return new_texture;
}

void array_texture_free(ArrayTexture *texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}
