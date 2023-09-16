#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common/log.h"

typedef struct {
    // the pointer to the GLFW window
    GLFWwindow *window;
} Window;


// Initializes a Window by creating a window context
void window_init(Window*, int, int, char*);

#endif
