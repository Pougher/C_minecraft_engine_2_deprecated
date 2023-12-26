#ifndef ECS_PHYSICS_H
#define ECS_PHYSICS_H

#include <cglm/cglm.h>

#include <math.h>
#include <stdbool.h>

#include "../block/block.h"

#include "../util/ext_math.h"

// constants that define the behavior of the physics system

// divide any value in metres by this value to obtain its position in the
// block worldspace
#define BLOCK_SCALAR 0.45

// the gravity of the physics engine in units (45cm each)
#define PHYSICS_GRAVITY 21.8f

struct Entity;

typedef struct {
    // the additional velocities that are added every physics tick
    vec3 av;

    // the velocity of the entity
    vec3 velocity;

    // boolean value to store wether or not the current physics object is
    // positioned on the ground
    bool grounded;

    // the drag coefficient of the object
    float drag_coefficient;

    // the area of the physics body projected onto a 2d plane
    float projected_area;

    // the density of the fluid that the object is in
    float fluid_density;

    // the mass of the falling object (kg)
    float mass;

    // the terminal velocity of the object
    float terminal_velocity;
} ECSphysics;

// initializes the physics object
void ecs_physics_init(ECSphysics*);

// constructs the physics objects' constants based off of set data. Should be
// called before any ticks take place
void ecs_physics_construct(ECSphysics*);

// ticks the physics - stuff like falling and hitting blocks, etc
void ecs_physics_tick(struct Entity*, ECSphysics*);

// ticks the physics per frame (adds velocity scaled by delta)
void ecs_physics_frame_tick(struct Entity*, ECSphysics*);

#endif
