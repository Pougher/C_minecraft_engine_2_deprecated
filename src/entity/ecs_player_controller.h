#ifndef ECS_PLAYER_CONTROLLER_H
#define ECS_PLAYER_CONTROLLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include "../common/camera.h"
#include "../common/types.h"

#include "ecs_physics.h"

struct Entity;

typedef struct {
    u8 EMPTY;
} ECSplayercontroller;

// doesn't really do anything
void ecs_playercontroller_init(ECSplayercontroller*);

// ticks the player controller on a per frame basis
void ecs_playercontroller_tick(struct Entity*, ECSplayercontroller*);

#endif
