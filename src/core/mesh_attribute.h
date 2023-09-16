#ifndef MESH_ATTRIBUTE_H
#define MESH_ATTRIBUTE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdint.h>

typedef struct {
    // the index into the buffer where the attribute is
    void *index;

    // the size of the attribute (1, 2, 3, 4)
    GLint size;

    // the type of the attribute
    GLenum type;

    // the size of the attribute in bytes
    uint8_t bytes;
} MeshAttribute;

#endif
