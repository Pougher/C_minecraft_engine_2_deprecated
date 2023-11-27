#include "ray.h"

void ray_init(Ray *ray) {
    glm_vec3_divs(ray->direction, ray->step, ray->direction);
}

void ray_step(Ray *ray) {
    glm_vec3_add(ray->pos, ray->direction, ray->pos);
}

void ray_step_fn(Ray *ray, void (*fn)(Ray*), i32 steps) {
    for (i32 i = 0; i < steps; i++) {
        glm_vec3_add(ray->pos, ray->direction, ray->pos);
        fn(ray);
    }
}
