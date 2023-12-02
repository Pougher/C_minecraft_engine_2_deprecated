#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render/shader.h"
#include "render/texture.h"
#include "common/log.h"
#include "common/camera.h"
#include "core/window.h"
#include "world/chunk.h"
#include "world/world.h"
#include "core/mesh.h"
#include "core/timer.h"

#include "render/grid_atlas.h"

#include "common/gamestate.h"

#include <cglm/cglm.h>

#define TPS 60

void init_glfw(void) {
    // initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void init_glew(void) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        log_error("Failed to initialize GLEW");
        glfwTerminate();
        exit(1);
    }
}

void mouse_callback(GLFWwindow *win, double xpos, double ypos) {
    Camera *cam = glfwGetWindowUserPointer(win);
    if (cam->first_mouse) {
        cam->last_x = xpos;
        cam->last_y = ypos;
        cam->first_mouse = 0;
    }

    float xoffset = xpos - cam->last_x;
    float yoffset = cam->last_y - ypos;
    cam->last_x = xpos;
    cam->last_y = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam->yaw += xoffset;
    cam->pitch += yoffset;

    if (cam->pitch > 89.0f) {
        cam->pitch = 89.0f;
    }
    if (cam->pitch < -89.0f) {
        cam->pitch = -89.0f;
    }

    cam->front[0] = cos(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    cam->front[1] = sin(glm_rad(cam->pitch));
    cam->front[2] = sin(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    glm_normalize(cam->front);
}

void mouse_click_callback(GLFWwindow *window,
    int button,
    int action,
    int mods) {
    (void) window;

    MouseState ms = {
        .button = button,
        .mods = mods,
        .action = action
    };

    ecs_mouse_update(state->ecs, &ms);
}

int main(void) {
    const double TICK_SPEED = 1.0 / TPS;

    init_glfw();

    Window win;
    window_init(&win, 1920, 1080, "Game");

    init_glew();

    glfwSetInputMode(win.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    gamestate_init("res/block_atlas.png",
        (char*[]) { "shaders/vs0.glsl", "shaders/fs0.glsl" },
        1);

    state->window = &win;

    Camera *cam = dynarray_get(state->ecs->camera,
        ecs_get_component_id(state->player, CAMERA));

    glfwSetWindowUserPointer(win.window, cam);

    glfwSetCursorPosCallback(win.window, mouse_callback);
    glfwSetMouseButtonCallback(win.window, mouse_click_callback);

    glfwSwapInterval(0);

    // gametick timer
    Timer gametick = {
        .interval = TICK_SPEED,
        .last_time = 0
    };

    // FPS timer
    Timer fps = {
        .interval = 1.0,
        .last_time = 0
    };

    int frames = 0;

    // for calculating delta time
    double start_frame = 0;

    shader_use(&state->shaders[0]);
    shader_setmat4(&state->shaders[0], "proj", cam->proj);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, state->block_atlas->atlas->id);

    while (!glfwWindowShouldClose(win.window)) {
        start_frame = glfwGetTime();

        glClearColor(0.509, 0.674, 1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_setmat4(&state->shaders[0], "view", cam->view);
        shader_setmat4(&state->shaders[0], "model", cam->model);
        shader_setint(&state->shaders[0], "tex", 0);
        world_render(state->world);

        camera_update(cam, win.window);

        glfwSwapBuffers(win.window);
        glfwPollEvents();

        state->delta = glfwGetTime() - start_frame;

        // update the physics engine
        if (timer_ready(&gametick)) {
            // update the ECS
            ecs_update(state->ecs);

            // update the world
            world_update(state->world);
        }

        frames++;
        if (timer_ready(&fps)) {
            char buffer[64];
            sprintf(buffer, "%d FPS", frames);
            log_info(buffer);
            frames = 0;
        }

        if (glfwGetKey(win.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }
    }

    gamestate_free();
    glfwTerminate();

    return 0;
}
