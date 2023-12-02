#include "ecs_block_break.h"
#include "../common/gamestate.h"

void ecs_blockbreak_init(ECSblockbreak *bb) {
    bb->cam = NULL;
    bb->pos = NULL;
}

void ecs_blockbreak_mouse_tick(ECSblockbreak *bb, MouseState *ms) {
    if (ms->button == GLFW_MOUSE_BUTTON_LEFT && ms->action == GLFW_PRESS) {
        Ray ray = {
            .step = 2048.0f
        };

        glm_vec3_copy(bb->cam->cam.front, ray.direction);
        glm_vec3_copy(*(bb->pos), ray.pos);

        ray_init(&ray);

        BlockType id;

        for (int i = 0; i < BLOCK_REACH * 2048; i++) {
            id = world_get_block(state->world,
                ray.pos[0],
                ray.pos[1],
                ray.pos[2]);
            if (id != AIR) {
                world_set_block(
                    state->world, ray.pos[0], ray.pos[1], ray.pos[2], AIR);
                break;
            }
            ray_step(&ray);
        }
    }
}
