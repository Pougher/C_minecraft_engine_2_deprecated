#include "ecs_camera.h"

void ecs_camera_init(ECScamera *camera) {
    camera_init(&camera->cam, (vec3) { 0.0f, 0.0f, 0.0f });
}
