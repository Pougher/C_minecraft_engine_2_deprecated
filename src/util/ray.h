#ifndef RAY_H
#define RAY_H

#include <cglm/cglm.h>

#include "../common/types.h"

typedef struct {
    // position vector, updated every time the ray is stepped
    vec3 pos;

    // the direction that the ray is pointing in as a unit vector
    vec3 direction;

    // the step of the vector each time it is traced
    float step;
} Ray;

// modifies the ray's parameters based off of the step parameter
void ray_init(Ray*);

// moves the ray one step forward
void ray_step(Ray*);

// moves the ray one step forward and calls a function
void ray_step_fn(Ray*, void (*)(Ray*), i32);

#endif
