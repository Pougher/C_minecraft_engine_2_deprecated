#include "window.h"

void window_init(Window *win, int w, int h, char *name) {
    win->window = glfwCreateWindow(w, h, name, NULL, NULL);

    if (win->window == NULL) {
        log_error("Could not initialize window context");
        glfwTerminate();
    }
    glfwMakeContextCurrent(win->window);
}
