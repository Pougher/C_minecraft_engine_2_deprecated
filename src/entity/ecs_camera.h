#ifndef ECS_CAMERA_H
#define ECS_CAMERA_H

#include "../common/camera.h"

typedef struct {
    Camera cam;
} ECScamera;

// creates a new camera object
void ecs_camera_init(ECScamera*);

#endif
