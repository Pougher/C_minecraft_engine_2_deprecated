#ifndef ECS_CAMERA_H
#define ECS_CAMERA_H

#include <math.h>

#include "../common/camera.h"

typedef struct {
    // the camera reference
    Camera cam;
} ECScamera;

// creates a new camera object
void ecs_camera_init(ECScamera*);

// ticks the camera
void ecs_camera_tick(ECScamera*);

#endif
