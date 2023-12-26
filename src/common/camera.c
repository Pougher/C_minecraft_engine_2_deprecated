#include "camera.h"
#include "gamestate.h"

// updates the camera's view matrix
static void camera_compute_view_matrix(Camera *cam) {
    vec3 temp;
    glm_vec3_add(*cam->pos, cam->front, temp);
    temp[1] -= 0.3f;

    // translate the player position down slightly, so that your head doesn't
    // clip into the block above your head
    vec3 pos;
    glm_vec3_copy(*cam->pos, pos);
    pos[1] -= 0.3f;

    glm_lookat(
        pos,
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
    const f32 speed = 15.0f * state->delta;
    f32 oldy = (*cam->pos)[1];
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
        CAMERA_SPEEDLR;
        glm_vec3_add(*cam->pos, CAMERA_RESULT, *cam->pos);
    }
    (*cam->pos)[1] = oldy;
    camera_compute_view_matrix(cam);
}
