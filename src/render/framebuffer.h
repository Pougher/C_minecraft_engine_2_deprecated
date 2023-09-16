#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "../common/log.h"
#include "texture.h"

typedef struct {
    // the framebuffer object
    unsigned int fbo;

    // renderbuffer attachment to the framebuffer
    unsigned int rbo;

    // width of the framebuffer
    int width;

    // height of the framebuffer
    int height;

    // the texture attachment for the framebuffer
    Texture *texture;
} Framebuffer;

// Creates a new OpenGL framebuffer object and attaches a renderbuffer and a
// texture. This means it can be rendered to. To ensure resources are freed
// correctly, call `framebuffer_free` when you are done using the
// framebuffer
Framebuffer *framebuffer_new(int, int);

// Instructs OpenGL to set the current framebuffer to the framebuffer provided
void framebuffer_use(Framebuffer*);

// Deletes a framebuffers fbo, rbo and texture objects
// Only use when your framebuffer is no longer in use
void framebuffer_free(Framebuffer*);

#endif
