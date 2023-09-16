#include "framebuffer.h"

Framebuffer *framebuffer_new(int width, int height) {
    Framebuffer *new_framebuffer = malloc(sizeof(Framebuffer));

    new_framebuffer->width = width;
    new_framebuffer->height = height;

    glGenFramebuffers(1, &new_framebuffer->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer->fbo);

    // Create a renderbuffer
    glGenRenderbuffers(1, &new_framebuffer->rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, new_framebuffer->rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        new_framebuffer->rbo);


    // create the texture
    new_framebuffer->texture = texture_empty(width, height, GL_RGBA);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        new_framebuffer->texture->id,
        0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        log_error("Failed to generate framebuffer");
        return new_framebuffer;
    }
#ifndef NO_LOGS
    char info[128];
    sprintf(
        info,
        "Generated framebuffer with ID %d and size %dx%d",
        new_framebuffer->fbo,
        width,
        height);
    log_info(info);
#endif

    return new_framebuffer;
}

void framebuffer_use(Framebuffer *framebuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
}

void framebuffer_free(Framebuffer *framebuffer) {
    glDeleteFramebuffers(1, &framebuffer->fbo);
    glDeleteRenderbuffers(1, &framebuffer->rbo);
    texture_free(framebuffer->texture);
    free(framebuffer);
}
