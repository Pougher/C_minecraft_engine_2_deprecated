#include "ecs_camera.h"

void ecs_camera_init(ECScamera *camera) {
    (void) camera;
    return;
}

void ecs_camera_tick(ECScamera *camera) {
    const double pitch = camera->cam.pitch * M_PI / 180.0f;
    const double yaw = camera->cam.yaw * M_PI / 180.0f;
    const double len = cos(pitch);

    camera->direction[0] = len * cos(yaw);
    camera->direction[1] = sin(pitch);
    camera->direction[2] = len * sin(-yaw);
}
