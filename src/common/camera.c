#include "camera.h"

// updates the camera's view matrix
static void camera_compute_view_matrix(Camera *cam) {
    vec3 temp;
    glm_vec3_add(*cam->pos, cam->front, temp);
    glm_lookat(
        *cam->pos,
        temp,
        cam->up,
        cam->view);
}

void camera_init(Camera *cam, vec3 *pos) {
    cam->pos = pos;

    // set the front of the camera and the up vector
    glm_vec3_copy((vec3) { 0.0f, 0.0f, -1.0f }, cam->front);
    glm_vec3_copy((vec3) { 0.0f, 1.0f, 0.0f }, cam->up);

    // calculate the model and projection matrices
    // for this I am using a perspective projection
    glm_perspective(glm_rad(80), 1.66666f, 0.1f, 1000.0f, cam->proj);

    glm_mat4_identity(cam->model);
    glm_translate(cam->model, (vec3) { 0.0f, 0.0f, -10.0f });

    // calculate the cameras view matrix
    camera_compute_view_matrix(cam);

    // set first mouse to true, since the mouse hasn't been interacted with
    // yet
    cam->first_mouse = 1;

    cam->last_x = 640;
    cam->last_y = 360;

    cam->pitch = 0.0f;
    cam->yaw = -90.0f;
}

void camera_update(Camera *cam, GLFWwindow *win) {
    static const f32 speed = 0.1f;
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
        CAMERA_SPEEDFW;
        glm_vec3_add(*cam->pos, CAMERA_RESULT, *cam->pos);
    }
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
        CAMERA_SPEEDFW;
        glm_vec3_sub(*cam->pos, CAMERA_RESULT, *cam->pos);
    }
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
        CAMERA_SPEEDLR;
        glm_vec3_sub(*cam->pos, CAMERA_RESULT, *cam->pos);
    }
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
        CAMERA_SPEEDLR;
        glm_vec3_add(*cam->pos, CAMERA_RESULT, *cam->pos);
    }
    camera_compute_view_matrix(cam);
}
