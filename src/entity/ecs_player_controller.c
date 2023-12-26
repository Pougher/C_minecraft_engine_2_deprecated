#include "ecs_player_controller.h"
#include "entity.h"

#include "../common/gamestate.h"

void ecs_playercontroller_init(ECSplayercontroller *component) {
    (void) component;
}

void ecs_playercontroller_tick(struct Entity *entity,
    ECSplayercontroller *component) {
    (void) component;

    GLFWwindow *win = state->window->window;

    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
        entity->physics->av[2] += entity->camera->cam.front[2] * 8.0f;
        entity->physics->av[0] += entity->camera->cam.front[0] * 8.0f;
    }
/*
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
        velo[2] += component->camera->front[2] * 8.0f;
        velo[0] += component->camera->front[0] * 8.0f;

        key_pressed = 1;
    } if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
        velo[2] += -component->camera->front[2] * 8.0f;
        velo[0] += -component->camera->front[0] * 8.0f;

        key_pressed = 1;
    } if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 result;
        glm_vec3_crossn(component->camera->front, pc->camera->up, result);
        velo[2] += -result[2] * 8.0f;
        velo[0] += -result[0] * 8.0f;

        key_pressed = 1;
    }*/
    if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS
        && entity->physics->grounded) {
        entity->physics->velocity[1] += 10.0f;
        //component->phys->next_ground = (*pc->phys->pos)[1];
    }
}
