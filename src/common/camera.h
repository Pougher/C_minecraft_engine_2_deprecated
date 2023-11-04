#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include "../core/window.h"

#include "../common/types.h"

#define CAMERA_RESULT tmp
#define CAMERA_SPEEDFW vec3 CAMERA_RESULT; \
    glm_vec3_scale(cam->front, speed, CAMERA_RESULT)
#define CAMERA_SPEEDLR vec3 CAMERA_RESULT; \
    glm_vec3_crossn(cam->front, cam->up, CAMERA_RESULT); \
    glm_vec3_scale(CAMERA_RESULT, speed, CAMERA_RESULT)

typedef struct {
    // pointer to the position of the camera
    vec3 *pos;

    // the front and up vectors of the camera
    vec3 front;
    vec3 up;

    // the camera's view matrix
    mat4 view;

    // the camera's model matrix
    mat4 model;

    // the camera's projection matrix
    mat4 proj;

    // camera mouse control variables
    i32 first_mouse;
    f64 last_x;
    f64 last_y;

    f32 yaw;
    f32 pitch;
} Camera;

// initializes a camera, initializing pos to the vector pointer passed to the
// function
void camera_init(Camera*, vec3*);

// updates the camera with the opengl context
void camera_update(Camera*, GLFWwindow*);

#endif
