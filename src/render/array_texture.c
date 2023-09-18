#include "array_texture.h"
#include "stb_image.h"

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

    // set the array textures parameters
    new_texture->width = width;
    new_texture->height = height;
    new_texture->images = count;

    glGenTextures(1, &new_texture->id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, new_texture->id);

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

    // free the loaded image data
    free(data);

    return new_texture;
}

void array_texture_free(ArrayTexture *texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}
